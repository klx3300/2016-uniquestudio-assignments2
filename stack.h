#define Q_STACK_H
#include <stdbool.h>
#include <stdlib.h>
#ifndef Q_LIST_H
#include "list.h"
#endif
#define qStack(Template) stack_constructor(sizeof(Template))
typedef double STACK_TYPE;
// TIPS: re-define the above identifiers
// in *.cpp file to make them shorter
// e.g. typedef T = STACK_TYPE;
// NOTE YOU CAN ONLY DO THAT IN *.cpp FILES

struct Stack{
     List *content;
};

typedef struct Stack Stack;

// functions 
// note the absence of reference
Stack* stack_constructor(int stepLength);
bool stack_empty(Stack* stk);
int stack_size(Stack* stk);

void stack_clear(Stack* stk);

void stack_push(Stack* stk, void* value);
void stack_pop(Stack* stk);
// return pointer to make it mutable is meaningless.
void* stack_top(Stack* stk);

