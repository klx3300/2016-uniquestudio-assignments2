#include "queue.h"
#include <string.h>

Queue* queue_constructor(int stepLength){
    Queue* tmp=malloc(sizeof(Queue));
    List* lst=list_constructor(stepLength);
    tmp->l=lst;
    return tmp;
}

bool queue_empty(Queue* queue){
    return list_empty(queue->l);
}

int queue_size(Queue* queue){
    return list_size(queue->l);
}

void queue_clear(Queue* queue){
    list_clear(queue->l);
}

void queue_push(Queue* queue,void* value){
    list_push_front(queue->l,value);
}

void queue_pop(Queue* queue){
    list_pop_back(queue->l);
}

void* queue_top(Queue* que){
    return que->l->last->ptr;
}
