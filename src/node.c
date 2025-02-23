#include <stdio.h>
#include "../include/node.h"

void nodePrint(const node_t * node) {
    switch (node->token)
    {
    case NUMBER:
        printf("n");
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
    case X_VAR:
        printf("x");
        break;
    case Y_VAR:
        printf("y");
        break;
    case Z_VAR:
        printf("z");
        break;
    case ENDOFLINE:
        printf("$");
        break;
    
    default:
        printf("&");
        break;
    }
}