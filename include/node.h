#ifndef NODE
#define NODE

#include "tokens.h"

struct node {
    token_t       token;
    struct node * next;
};

typedef struct node node_t;

void nodePrint(node_t *);

#endif//NODE