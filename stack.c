#include "stack.h"
Stack* stack_constructor(int stepLength){
    Stack *tmpstk=malloc(sizeof(Stack));
    tmpstk->content=vector_constructor(stepLength);
    return tmpstk;
}

bool stack_empty(Stack* stk){
    return vector_empty(stk->content);
}

int stack_size(Stack* stk){
    return vector_size(stk->content);
}

void stack_clear(Stack* stk){
    vector_clear(stk->content);
}

void stack_push(Stack* stk,void* value){
    vector_push_back(stk->content,value);
}

void stack_pop(Stack* stk){
    vector_pop_back(stk->content);
}

void* stack_top(Stack* stk){
    return stk->content->arr+((stk->content->counts-1)*stk->content->step);
}
