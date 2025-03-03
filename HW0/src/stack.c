#include <stdlib.h>
#include <stdio.h>
#include "../include/stack.h"

stack_t * stackCtor() {
    stack_t * stk = (stack_t *) malloc(sizeof(stack_t));
    if (!stk) {
        perror("Stack allocation error");
        return NULL;
    }
    stk->head = NULL;
    stk->size = 0;
    return stk;
}

void stackDtor(stack_t * stk) {
    if (!stk) {
        printf("NULL in stackDtor\n");
        return;
    }
    node_t * curent_node = stk->head;
    while (curent_node) {
        node_t * previous_node = curent_node;
        curent_node = curent_node->next;
        free(previous_node);
    }
    free(stk);
}

void stackPush(stack_t * stk, int value) {
    if (!stk) {
        printf("NULL in stackPush\n");
        return;
    }
    node_t * new_node = (node_t *) malloc(sizeof(node_t));
    if (!new_node) {
        perror("Node allocate error");
        return;
    }
    new_node->next = stk->head;
    new_node->prev = NULL;
    new_node->value = value;
    stk->head = new_node;
    stk->size++;
}

int stackPop(stack_t * stk) {
    if (!stk) {
        printf("NULL in stackPop\n");
        return ERROR;
    }
    if (!stk->head) {
        printf("Stack is empty\n");
        return 0;
    }
    node_t * pop_node = stk->head;
    stk->head = pop_node->next;
    stk->size--;
    token_t token = pop_node->value;
    free(pop_node);
    return token;
}

int stackTop(const stack_t * stk) {
    if (!stk) {
        printf("NULL in stackTop\n");
        return ERROR;
    }
    if (!stk->head) {
        //printf("Stack is empty\n");
        return 0;
    }
    return stk->head->value;
}

void StackNodePrint(node_t * stk_node, int flag) {
    if (!stk_node) return;
    StackNodePrint(stk_node->next, flag);
    nodePrint(stk_node, flag);
}

void stackPrint(const stack_t * stk, int flag) {
    printf("$");
    StackNodePrint(stk->head, flag);
}
