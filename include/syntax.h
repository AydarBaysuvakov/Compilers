#ifndef SYNTAX
#define SYNTAX

#include "stack.h"
#include "list.h"

typedef enum {
    LR0 ,
    LR1 ,
    NONE
} grammar_t ;

typedef struct syntax_analyzer {
    grammar_t grammar;
    stack_t * stk;
    list_t  * lst;
} syntax_analyzer_t ;

syntax_analyzer_t * syntax_analyzerCtor (grammar_t);
void                syntax_analyzerDtor (syntax_analyzer_t *);

#endif//SYNTAX