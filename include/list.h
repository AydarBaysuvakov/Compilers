#ifndef LIST
#define LIST

#include "node.h"

typedef struct list {
    node_t * head;
    node_t * tail;
    node_t * curent;
    unsigned size;
} list_t;

list_t *  listCtor  ();
void      listDtor  (list_t *);
void      listAdd   (list_t *, token_t token);
token_t   listCurent(list_t *);
token_t   listNext  (list_t *);
void      listPrint (const list_t *);

#endif//LIST