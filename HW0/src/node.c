#include <stdio.h>
#include "../include/node.h"

void nodePrint(const node_t * node, int flag) {
    if (flag) {
        printf("%d ", node->value);
        return;
    }
    switch (node->value)
    {
    case NUMBER:
        printf("N");
        break;
    case PLUS:
        printf("+");
        break;
    case MINUS:
        printf("-");
        break;
    case MULTIPLY:
        printf("*");
        break;
    case DIVIDE:
        printf("/");
        break;
    case OPEN_B:
        printf("(");
        break;
    case CLOSE_B:
        printf(")");
        break;
    case X_VAR:
        printf("X");
        break;
    case Y_VAR:
        printf("Y");
        break;
    case Z_VAR:
        printf("Z");
        break;
    case EXPRESSION:
        printf("E");
        break;
    case TERM:
        printf("T");
        break;
    case PARAMETR:
        printf("F");
        break;
    case ENDOFLINE:
        printf("$");
        break;
    
    default:
        printf("&");
        break;
    }
}