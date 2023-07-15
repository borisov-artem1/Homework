#include "ceml_parse.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char* string;
    int size;
    int memory;
} string_t;

typedef struct {
    string_t *from;
    string_t *to;
    string_t *date;
    string_t *boundary;
    int amount_of_parts;
} hdrs_t;


typedef enum {
    L_SOME_CHAR,
    L_COLON,
    L_WS,
    L_NEW_LINE,
    L_HEAD_END,
    L_COUNT,
    L_ERR
} lexem_t;


typedef enum {
    S_HEAD_BEGIN,
    S_HDR_BEGIN,
    S_COLON,
    S_HDR_VALUE,
    S_NEW_LINE,
    S_WS,
    S_HEAD_END,
    S_COUNT,
    S_ERR
} state_t;



static state_t transitions[S_COUNT][L_COUNT] = {
        // L_SOME_CHAR            L_COLON               L_WS                 L_NEW_LINE         L_HEAD_END
    /* S_HEAD_BEGIN */{S_HDR_BEGIN,     S_ERR,          S_HEAD_BEGIN,    S_NEW_LINE,     S_HEAD_END},
    /* S_HDR_BEGIN */ {S_HDR_BEGIN,     S_COLON,        S_HDR_BEGIN,     S_NEW_LINE,     S_ERR},
    /* S_COLON */     {S_HDR_VALUE,     S_ERR,          S_COLON,         S_NEW_LINE,     S_ERR},
    /* S_HDR_VALUE */ {S_HDR_VALUE,     S_HDR_VALUE,    S_HDR_VALUE,     S_NEW_LINE,     S_HEAD_END},
    /* S_NEW_LINE */  {S_HDR_BEGIN,     S_ERR,          S_HDR_VALUE,     S_HEAD_END,     S_HEAD_END},
    /* S_WS */        {S_HDR_VALUE,     S_COLON,        S_WS,            S_NEW_LINE,     S_HEAD_END},
    /* S_HEAD_END */  {S_ERR,           S_ERR,          S_ERR,           S_ERR,          S_HEAD_END}
};

static bool compare_hdrs(const char* expected_string, string_t *received_string) {
    if (!received_string || !received_string->string) {
        return false;
    }
    return strcmp(received_string->string, expected_string) == 0;
}

string_t *init_string(void) {
    string_t *ch_arr = calloc(1, sizeof(string_t));
    ch_arr->size = 1;
    ch_arr->memory = 0;
    return ch_arr;
}

void add_char(string_t *data, char current_sym) {
    if (current_sym == '\r') {
        return;
    }
    ++data->size;
    if (data->string == NULL) {
        data->string = calloc(10, data->size);
        data->memory += 10;
    } else if (data->size > data->memory) {
        data->memory *= data->memory;
        char *tmp = (char*) realloc(data->string, data->memory);
        if (!tmp) {
            return;
        }
        data->string = tmp;
    }
    data->string[data->size - 2] = current_sym;
    data->string[data->size - 1] = '\0';
}
lexem_t get_lexem(char current_sym, state_t prev_state) {
    if (prev_state == S_NEW_LINE) {
        switch (current_sym) {
            case '\n': return L_HEAD_END;
            case ' ': return L_SOME_CHAR;
            case '\t': return L_SOME_CHAR;
            case '\r': return L_NEW_LINE;
            default: break;
        }
    }
    switch (current_sym) {
        case '\n': return L_NEW_LINE;
        case ' ': return L_WS;
        case '\t': return L_WS;
        case ':': return L_COLON;
        case '\r': return L_WS;
        default: return L_SOME_CHAR;
    }
    return L_ERR;
}

string_t* get_boundary(string_t *value) {
    string_t *boundary = init_string();
    if (!value || !value->string) {
        return boundary;
    }
    char *ptr = strstr(value->string, "boundary=");
    if (ptr == NULL) {
        ptr = strstr(value->string, "BOUNDARY=");
    }
    if (ptr == NULL) {
        return boundary;
    }
    if (*(ptr - 1) == 'x') {
        return boundary;
    }
    ptr += 9;
    if (*ptr == '"') {
        ++ptr;
    }
    while (*ptr != '"' && *ptr != ' ' && *ptr != '\n' && *ptr != '\r' && *ptr != '\0') {
        add_char(boundary, *ptr);
        ++ptr;
    }
    return boundary;
}

void free_string(string_t* data) {
    if (data != NULL && data->string != NULL) {
        free(data->string);
    }
    free(data);
}

static hdrs_t extract_hdrs(FILE *eml_file) {
    hdrs_t data = {0};
    state_t state = S_HEAD_BEGIN;
    state_t prev_state = state;
    string_t *value = init_string();
    string_t *header = init_string();
    while (state != S_HEAD_END) {
        char current_sym = fgetc(eml_file);
        lexem_t lexem = get_lexem(current_sym, prev_state);
        prev_state = state;
        state = transitions[state][lexem];
        if ((state == S_HDR_BEGIN && prev_state == S_NEW_LINE) || state == S_HEAD_END) {
            if (compare_hdrs("From", header)) {
                data.from = value;
            } else if (compare_hdrs("To", header)) {
                data.to = value;
            } else if (compare_hdrs("Date", header)) {
                data.date = value;
            } else if (compare_hdrs("Content-Type", header)) {
                data.boundary = get_boundary(value);
                free_string(value);
            } else {
                free_string(value);
            }
            free_string(header);
            header = init_string();
            value = init_string();
            add_char(header, current_sym);
        } else if (state == S_HDR_BEGIN) {
            add_char(header, current_sym);
        } else if (state == S_HDR_VALUE) {
            add_char(value, current_sym);
        } else if (state == S_ERR) {
            if (header || value) {
                if (header) {
                    free_string(header);
                }
                if (value) {
                    free_string(value);
                }
            }
            return data;
        }
    }
    free_string(header);
    free_string(value);
    return data;
}

int parse_body_count(char *body, string_t* boundary) {
    char *flg = strstr(body, boundary->string);
    char *ptr = body;
    int counter = 0;
    while (flg != NULL) {
        ++counter;
        ptr = flg;
        flg = strstr(flg + boundary->size, boundary->string);
    }
    while (*ptr != '\n' && *ptr != '\0') { ++ptr; }
    while (*ptr == ' ' || *ptr == '\n' || *ptr == '\t' || *ptr == '\r' || *ptr == '.' || *ptr == '=') ++ptr;
    if (counter != 0 && *ptr == '\0') {
        return counter - 1;
    } else {
        return counter;
    }
}

void ceml_parse(FILE *eml_file) {
    fseek(eml_file, 0, SEEK_END);
    int eml_length = ftell(eml_file);
    fseek(eml_file, 0, SEEK_SET);

    hdrs_t data = extract_hdrs(eml_file);

    size_t body_length = eml_length - ftell(eml_file);
    char *body = (char*) calloc(1, body_length + 1);
    fread(body, 1, body_length, eml_file);
    body[body_length] = '\0';
    data.amount_of_parts = (data.boundary == NULL) || (data.boundary->string == NULL) ?
    1 : parse_body_count(body, data.boundary);
    printf("%s|%s|%s|%d",
           data.from == NULL ? "" : data.from->string,
           data.to == NULL ? "" : data.to->string,
           data.date == NULL ? "" : data.date->string,
           data.amount_of_parts);
    free(body);
    free_string(data.from);
    free_string(data.to);
    free_string(data.date);
    free_string(data.boundary);
}

