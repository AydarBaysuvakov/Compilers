#ifndef NODE
#define NODE

#include "tokens.h"

struct node {
    int           value;
    struct node * next;
    struct node * prev;
};

typedef struct node node_t;

void nodePrint(const node_t *, int);

#endif//NODE