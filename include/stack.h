#ifndef STACK
#define STACK

#include "node.h"

typedef struct stack {
    node_t * head;
    unsigned size;
} stack_t;

stack_t * stackCtor ();
void      stackDtor (stack_t *);
void      stackPush (stack_t *, token_t token);
token_t   stackPop  (stack_t *);
token_t   stackTop  (const stack_t *);
void      stackPrint(const stack_t *);

#endif//STACK