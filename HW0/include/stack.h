#ifndef STACK
#define STACK

#include "node.h"

typedef struct stack {
    node_t * head;
    unsigned size;
} stack_t;

stack_t * stackCtor ();
void      stackDtor (stack_t *);
void      stackPush (stack_t *, int value);
int       stackPop  (stack_t *);
int       stackTop  (const stack_t *);
void      stackPrint(const stack_t *, int);

#endif//STACK