#include <stdlib.h>
#include <stdio.h>
#include "../include/list.h"

list_t *  listCtor  () {
    list_t * lst = (list_t *) malloc(sizeof(list_t));
    if (!lst) {
        perror("List allocation error");
        return NULL;
    }
    lst->head = NULL;
    lst->tail = NULL;
    lst->curent = NULL;
    lst->size = 0;
    return lst;
}

void listDtor(list_t * lst) {
    if (!lst) {
        printf("NULL in listDtor\n");
        return;
    }
    node_t * curent_node = lst->head;
    while (curent_node) {
        node_t * previous_node = curent_node;
        curent_node = curent_node->next;
        free(previous_node);
    }
    free(lst);
}

void listAdd(list_t * lst, token_t token) {
    if (!lst) {
        printf("NULL in listAdd\n");
        return;
    }
    node_t * new_node = (node_t *) malloc(sizeof(node_t));
    if (!new_node) {
        perror("Node allocate error");
        return;
    }
    new_node->next = NULL;
    new_node->prev = lst->tail;
    new_node->value = token;

    if (!lst->head) lst->head = new_node;
    if (!lst->curent) lst->curent = new_node;
    if (lst->tail) lst->tail->next = new_node;
    lst->tail = new_node;
    lst->size++;
}

int listNext(list_t * lst) {
    if (!lst) {
        printf("NULL in listNext\n");
        return ERROR;
    }
    lst->curent = lst->curent->next;
    return lst->curent->value;
}

int listCurent(list_t * lst) {
    if (!lst) {
        printf("NULL in listCurent\n");
        return ERROR;
    }
    return lst->curent->value;
}

int listPrev(list_t * lst) {
    if (!lst) {
        printf("NULL in listNext\n");
        return ERROR;
    }
    lst->curent = lst->curent->prev;
    return lst->curent->value;
}

void listPrint(const list_t * lst) {
    node_t * cur = lst->curent;
    while (cur) {
        nodePrint(cur, 0);
        cur = cur->next;
    }
}