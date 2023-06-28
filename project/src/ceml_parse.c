#include "ceml_parse.h"
#include <stdlib.h>
#include <stdbool.h>
/*
 * somechar
 * colon
 * ws
 * tab
 * trans_sym
 * ddash
 * bound
 * lexems
 *
 * begin
 * key
 * value
 * trans_sym
 * body
 * ddash
 * bound
 * end
 *
 */
typedef enum {
    L_SOME_CHAR,
    L_COLON,
    L_WS,
    L_TAB,
    L_TRANS,
    L_DDASH,
    L_BOUNDARY,
    L_COUNT,
    L_ERR
} lexem_t;


typedef enum {
    S_BEGIN,
    S_KEY,
    S_VALUE,
    S_TRANS_SYM,
    S_BODY,
    S_DDASH,
    S_BOUNDARY,
    S_END,
    S_COUNT,
    S_ERR
} state_t;



typedef bool (*action_t)(const char *s, const char **end);

typedef struct {
    state_t state;
    action_t action;
} rule_t;

static rule_t transitions[S_COUNT][L_COUNT] = {
                        //             L_SOME_CHAR                        L_COLON                           L_WS                           L_TAB                            L_TRANS                        L_DDASH                      L_BOUNDARY
    /* S_BEGIN */      {{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL }},
    /* S_KEY */        {{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL }},
    /* S_VALUE */      {{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL }},
    /* S_TRANS_SYM */  {{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL }},
    /* S_BODY */       {{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL }},
    /* S_DDASH */      {{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL }},
    /* S_BOUNDARY */   {{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL }},
    /* S_END */        {{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL },{ S_ERR, NULL }},
};

bool ceml_parse (const char* eml) {
    FILE* eml_file = fopen(eml, "r+");
    if (!eml_file) {
        puts("file doesn't opened");
        return false;
    }
    state_t state = S_BEGIN;

    return true;
}

