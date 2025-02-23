#include <stdio.h>
#include <stdlib.h>
#include "../include/syntax.h"

syntax_analyzer_t * syntax_analyzerCtor (grammar_t t) {
    if (t == LR0) {
        syntax_analyzer_t * sa = (syntax_analyzer_t *) malloc(sizeof(syntax_analyzer_t));
        sa->grammar = t;
        sa->stk = stackCtor();
        sa->lst = listCtor();

        token_t token;
        while ((token = getNextToken()) != ENDOFLINE) {
            listAdd(sa->lst, token);
        }
        listAdd(sa->lst, ENDOFLINE);
        listPrint(sa->lst);
        return sa;
    }
    else {
        printf("Unknown grammar\n");
        return NULL;
    }
}

void syntax_analyzerDtor (syntax_analyzer_t * sa) {
    if (!sa) {
        printf("NULL in syntax_analizerDtor");
        return;
    }
    stackDtor(sa->stk);
    listDtor(sa->lst);
    free(sa);
}

