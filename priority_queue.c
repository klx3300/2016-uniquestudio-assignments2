#include "priority_queue.h"
#include "voidutils.h"
#include <string.h>
#ifndef Q_VECTOR_H
#include "vector.h"
#endif

PriorityQueue* priority_queue_constructor(int step,int (*cmp)(void*,void*)){
    PriorityQueue* p=malloc(sizeof(PriorityQueue));
    p->heap=vector_constructor(step);
    p->cmp=cmp;
    vector_push_back(p->heap,malloc(step));// heap structure doesn't use the first element.
    return p;
}

bool priority_queue_empty(PriorityQueue* queue){
    return vector_empty(queue->heap);
}

int priority_queue_size(PriorityQueue* queue){
    return vector_size(queue->heap);
}

void priority_queue_clear(PriorityQueue* queue){
    vector_clear(queue->heap);
}

void* priority_queue_top(PriorityQueue* queue){
    return vector_ptr_at(queue->heap)+(queue->heap->step);
}

void priority_queue_push(PriorityQueue* queue,void* value){
    vector_push_back(queue->heap,value);
    heap_swim(queue->heap,queue->cmp);
}

void priority_queue_pop(PriorityQueue* queue){
    heap_pop(queue->heap);
    heap_sink(queue->heap,queue->cmp);
}
