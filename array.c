#include "array.h"

Array* array_constructor(int step,int maxlength){
    Array* ptr=malloc(sizeof(Array));
    ptr->content=malloc(step*maxlength);
    ptr->maxlength=maxlength;
    ptr->step=step;
    return ptr;
}

void* array_ptr_at(Array* arr){
    return arr->content;
}

bool array_empty(Array* arr){
    return arr->content==NULL;
}

int array_size(Array* arr){
    return arr->maxlength;
}

int array_max_size(Array* arr){
    return arr->maxlength;
}
