#include "stack.h"
#include "voidutils.h"
Stack* stack_constructor(int stepLength){
    Stack *tmpstk=malloc(sizeof(List));
    tmpstk->content=list_constructor(stepLength);
    return tmpstk;
}

bool stack_empty(Stack* stk){
    return list_empty(stk->content);
}

int stack_size(Stack* stk){
    return list_size(stk->content);
}

void stack_clear(Stack* stk){
    list_clear(stk->content);
}

void stack_push(Stack* stk,void* value){
    qLog("STACK PUSH");
    list_push_back(stk->content,value);
}

void stack_pop(Stack* stk){
    qLog("STACK POP");
    list_pop_back(stk->content);
}

void* stack_top(Stack* stk){
    return stk->content->last->ptr;
}
