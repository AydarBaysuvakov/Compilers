#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/syntax.h"

void printTable() {
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|                       Stack                       |              Symbols              |              Input              |            Action            |\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

syntax_analyzer_t * syntax_analyzerCtor (grammar_t t) {
    if (t == LR0) {
        syntax_analyzer_t * sa = (syntax_analyzer_t *) malloc(sizeof(syntax_analyzer_t));
        sa->grammar = t;
        sa->dfsm = stackCtor();
        sa->stk  = stackCtor();
        sa->lst  = listCtor();
        stackPush(sa->dfsm, 0);

        token_t token;
        while ((token = getNextToken()) != ENDOFLINE) {
            listAdd(sa->lst, token);
        }
        listAdd(sa->lst, ENDOFLINE);
        printTable();
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
    stackDtor(sa->dfsm);
    stackDtor(sa->stk);
    listDtor(sa->lst);
    free(sa);
}

void printState(syntax_analyzer_t * sa) {
    printf("|  ");
    stackPrint(sa->dfsm, 1);
    printf("\e[53G|  ");
    stackPrint(sa->stk, 0);
    printf("\e[89G|  ");
    listPrint(sa->lst);
    printf("\e[123G|  ");
}

int I0(syntax_analyzer_t * sa) {
    token_t token = sa->lst->curent->value;
    switch (token)
    {
    case EXPRESSION:
        stackPush(sa->dfsm, 1);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 1");
        break;
    case TERM:
        stackPush(sa->dfsm, 2);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 2");
        break;
    case PLUS:
    case MINUS:
        stackPush(sa->dfsm, 3);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 3");
        break;
    case PARAMETR:
        stackPush(sa->dfsm, 4);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 4");
        break;
    case OPEN_B:
        stackPush(sa->dfsm, 5);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 5");
        break;
    case NUMBER:
    case X_VAR:
    case Y_VAR:
    case Z_VAR:
        stackPush(sa->dfsm, 6);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 6");
        break;
    
    default:
        printf("error");
        return -1;
        break;
    }
    return 0;
}

int I1(syntax_analyzer_t * sa) {
    printf("accept");
    return 1;
}

int I2(syntax_analyzer_t * sa) {
    token_t token = sa->lst->curent->value;
    switch (token)
    {
    case PLUS:
    case MINUS:
        stackPush(sa->dfsm, 7);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 7");
        break;
    
    default:
        // reduce T
        stackPop(sa->dfsm);
        stackPop(sa->stk);

        listPrev(sa->lst);
        sa->lst->curent->value = EXPRESSION;

        printf("reduce E -> T");
    }
    return 0;
}

int I3(syntax_analyzer_t * sa) {
    token_t token = sa->lst->curent->value;
    switch (token)
    {
    case TERM:
        stackPush(sa->dfsm, 8);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 8");
        break;
    case PARAMETR:
        stackPush(sa->dfsm, 4);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 4");
        break;
    case OPEN_B:
        stackPush(sa->dfsm, 5);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 5");
        break;
    case NUMBER:
    case X_VAR:
    case Y_VAR:
    case Z_VAR:
        stackPush(sa->dfsm, 6);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 6");
        break;
    
    default:
        printf("error");
        return -1;
        break;
    }
    return 0;
}

int I4(syntax_analyzer_t * sa) {
    token_t token = sa->lst->curent->value;
    switch (token)
    {
    case MULTIPLY:
    case DIVIDE:
        stackPush(sa->dfsm, 9);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 9");
        break;
    
    default:
        // reduce F
        stackPop(sa->dfsm);
        stackPop(sa->stk);

        listPrev(sa->lst);
        sa->lst->curent->value = TERM;

        printf("reduce T -> F");
    }
    return 0;
}

int I5(syntax_analyzer_t * sa) {
    token_t token = sa->lst->curent->value;
    switch (token)
    {
    case EXPRESSION:
        stackPush(sa->dfsm, 10);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 10");
        break;
    case TERM:
        stackPush(sa->dfsm, 2);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 2");
        break;
    case PLUS:
    case MINUS:
        stackPush(sa->dfsm, 3);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 3");
        break;
    case PARAMETR:
        stackPush(sa->dfsm, 4);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 4");
        break;
    case OPEN_B:
        stackPush(sa->dfsm, 5);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 5");
        break;
    case NUMBER:
    case X_VAR:
    case Y_VAR:
    case Z_VAR:
        stackPush(sa->dfsm, 6);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 6");
        break;
    
    default:
        printf("error");
        return -1;
        break;
    }
    return 0;
}

int I6(syntax_analyzer_t * sa) {
    stackPop(sa->dfsm);
    stackPop(sa->stk);
    listPrev(sa->lst);
    sa->lst->curent->value = PARAMETR;

    printf("reduce F -> id");
    return 0;
}

int I7(syntax_analyzer_t * sa) {
    token_t token = sa->lst->curent->value;
    switch (token)
    {
    case TERM:
        stackPush(sa->dfsm, 11);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 11");
        break;
    case PARAMETR:
        stackPush(sa->dfsm, 4);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 4");
        break;
    case OPEN_B:
        stackPush(sa->dfsm, 5);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 5");
        break;
    case NUMBER:
    case X_VAR:
    case Y_VAR:
    case Z_VAR:
        stackPush(sa->dfsm, 6);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 6");
        break;
    
    default:
        printf("error");
        return -1;
        break;
    }
    return 0;
}

int I8(syntax_analyzer_t * sa) {
    token_t token = sa->lst->curent->value;
    switch (token)
    {
    case PLUS:
    case MINUS:
        stackPush(sa->dfsm, 3);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 3");
        break;
    
    default:
        while (stackTop(sa->stk) == TERM)
        {
            // reduce T
            stackPop(sa->dfsm);
            stackPop(sa->stk);
            // reduce [+-]
            stackPop(sa->dfsm);
            stackPop(sa->stk);
        }
        listPrev(sa->lst);
        sa->lst->curent->value = EXPRESSION;

        printf("reduce E -> {[+-]T}+");
    }
    return 0;
}

int I9(syntax_analyzer_t * sa) {
    token_t token = sa->lst->curent->value;
    switch (token)
    {
    case PARAMETR:
        stackPush(sa->dfsm, 12);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 12");
        break;
    case OPEN_B:
        stackPush(sa->dfsm, 5);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 5");
        break;
    case NUMBER:
    case X_VAR:
    case Y_VAR:
    case Z_VAR:
        stackPush(sa->dfsm, 6);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 6");
        break;
    
    default:
        printf("error");
        return -1;
        break;
    }
    return 0;
}

int I10(syntax_analyzer_t * sa) {
    token_t token = sa->lst->curent->value;
    switch (token)
    {
    case CLOSE_B:
        stackPush(sa->dfsm, 13);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 13");
        break;
    
    default:
        printf("error");
        return -1;
        break;
    }
    return 0;
}

int I11(syntax_analyzer_t * sa) {
    token_t token = sa->lst->curent->value;
    switch (token)
    {
    case PLUS:
    case MINUS:
        stackPush(sa->dfsm, 7);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 7");
        break;
    
    default:
        // reduce T
        stackPop(sa->dfsm);
        stackPop(sa->stk);
        while (stackTop(sa->stk) == PLUS || stackTop(sa->stk) == MINUS)
        {
            // reduce [+-]
            stackPop(sa->dfsm);
            stackPop(sa->stk);
            // reduce T
            stackPop(sa->dfsm);
            stackPop(sa->stk);
        }

        listPrev(sa->lst);
        sa->lst->curent->value = EXPRESSION;

        printf("reduce E -> T{[+-]T}+");
    }
    return 0;
}

int I12(syntax_analyzer_t * sa) {
    token_t token = sa->lst->curent->value;
    switch (token)
    {
    case MULTIPLY:
    case DIVIDE:
        stackPush(sa->dfsm, 9);
        stackPush(sa->stk, token);
        listNext(sa->lst);
        printf("Shift to 9");
        break;
    
    default:
        // reduce F
        stackPop(sa->dfsm);
        stackPop(sa->stk);
        while (stackTop(sa->stk) == MULTIPLY || stackTop(sa->stk) == DIVIDE)
        {
            // reduce [*/]
            stackPop(sa->dfsm);
            stackPop(sa->stk);
            // reduce F
            stackPop(sa->dfsm);
            stackPop(sa->stk);
        }

        listPrev(sa->lst);
        sa->lst->curent->value = TERM;

        printf("reduce T -> F{[*/]F}+");
    }
    return 0;
}

int I13(syntax_analyzer_t * sa) {
    // reduce )
    stackPop(sa->dfsm);
    stackPop(sa->stk);
    // reduce E
    stackPop(sa->dfsm);
    stackPop(sa->stk);
    // reduce (
    stackPop(sa->dfsm);
    stackPop(sa->stk);

    listPrev(sa->lst);
    sa->lst->curent->value = PARAMETR;

    printf("reduce F -> (E)");
    return 0;
}

int syntax_analysis(syntax_analyzer_t * sa) {
    assert(sa);
    int state = 0;

    while (state == 0) {
        printState(sa);
        switch (stackTop(sa->dfsm))
        {
        case 0:
            state = I0(sa);
            break;
        case 1:
            state = I1(sa);
            break;
        case 2:
            state = I2(sa);
            break;
        case 3:
            state = I3(sa);
            break;
        case 4:
            state = I4(sa);
            break;
        case 5:
            state = I5(sa);
            break;
        case 6:
            state = I6(sa);
            break;
        case 7:
            state = I7(sa);
            break;
        case 8:
            state = I8(sa);
            break;
        case 9:
            state = I9(sa);
            break;
        case 10:
            state = I10(sa);
            break;
        case 11:
            state = I11(sa);
            break;
        case 12:
            state = I12(sa);
            break;
        case 13:
            state = I13(sa);
            break;
        
        default:
            break;
        }
        printf("\e[154G|\n");
    }
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

