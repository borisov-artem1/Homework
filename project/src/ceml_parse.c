#include "ceml_parse.h"
#include <stdlib.h>
/* begin
 * head_name
 * collon
 * head_value
 * trans_sym
 * more_head_value
 * more_trans_sym
 * body
 * multi_body
 * end
 * error
 * lexems (str, :, , /n, --boundary, --boundary--)
 * */
typedef enum {
    L_STR,
    L_COLLON,
    L_WS,
    L_TRANS_SYM,
    L_TBOUND,
    L_BBOUND,
    L_COUNT,
    L_ERR
} lexem_t;

typedef enum {
    S_BEGIN,
    S_HEAD_NAME,
    S_COLLON,
    S_HEAD_VALUE,
    S_TRANS_SYM,
    S_MORE_HEAD_VALUE,
    S_MORE_TRANS_SYM,
    S_BODY,
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
                           // L_STR                         L_COLLON            L_WS                         L_TRANS_SYM                  L_TBOUND         L_BBOUND
    /* S_BEGIN */          {{ S_HEAD_NAME, NULL },          { S_ERR, NULL },    { S_ERR, NULL },             { S_ERR, NULL },            { S_ERR, NULL },  { S_ERR, NULL }},
    /* S_HEAD_NAME */      {{ S_ERR, NULL },                { S_COLLON, NULL }, { S_ERR, NULL },             { S_ERR, NULL },            { S_ERR, NULL },  { S_ERR, NULL }},
    /* S_COLLON */         {{ S_ERR, NULL },                { S_ERR, NULL },    { S_HEAD_VALUE, NULL },      { S_ERR, NULL },            { S_ERR, NULL },  { S_ERR, NULL }},
    /* S_HEAD_VALUE */     {{ S_ERR, NULL },                { S_ERR, NULL },    { S_ERR, NULL },             { S_TRANS_SYM, NULL },      { S_ERR, NULL },  { S_ERR, NULL }},
    /* S_TRANS_SYM */      {{ S_HEAD_NAME, rule_t.action }, { S_ERR, NULL },    { S_MORE_HEAD_VALUE, NULL }, { S_MORE_TRANS_SYM, NULL }, { S_BODY, NULL }, { S_END, NULL }},
    /* S_MORE_HEAD_VALUE */{{ S_ERR, NULL },                { S_ERR, NULL },    { S_ERR, NULL },             { S_TRANS_SYM, NULL },      { S_BODY, NULL }, { S_END, NULL }},
    /* S_MORE_TRANS_SYM */ {{ S_ERR, NULL },                { S_ERR, NULL },    { S_ERR, NULL },             { S_TRANS_SYM, NULL },      { S_BODY, NULL }, { S_END, NULL }},
    /* S_BODY */           {{ S_ERR, NULL },                { S_ERR, NULL },    { S_ERR, NULL },             { S_ERR, NULL },            { S_ERR, NULL },  { S_END, NULL }},
    /* S_END */            {{ S_ERR, NULL },                { S_ERR, NULL },    { S_ERR, NULL },             { S_ERR, NULL },            { S_ERR, NULL },  { S_ERR, NULL }},
    /* S_COUNT */          {{ S_ERR, NULL },                { S_ERR, NULL },    { S_ERR, NULL },             { S_ERR, NULL },            { S_ERR, NULL },  { S_ERR, NULL }},
    /* S_ERR */            {{ S_ERR, NULL },                { S_ERR, NULL },    { S_ERR, NULL },             { S_ERR, NULL },            { S_ERR, NULL },  { S_ERR, NULL }},
};

