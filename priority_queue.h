#include <stdbool.h>
#include <stdlib.h>
#ifndef Q_VECTOR_H
#include "vector.h"
#endif

#define qPriorityQueue(Template,Comparer) priority_queue_constructor(sizeof(Template),Comparer);

typedef double PRIORITY_QUEUE_TYPE;
// TIPS: re-define the above identifiers
// in *.cpp file to make them shorter
// e.g. typedef T = PRIORITY_QUEUE_TYPE;
// NOTE YOU CAN ONLY DO THAT IN *.cpp FILES

struct PriorityQueue{
    Vector* heap;
    int (*cmp)(void*,void*);
};

typedef struct PriorityQueue PriorityQueue;

// functions 
// note the absence of reference
PriorityQueue* priority_queue_constructor(int step,int (*cmp)(void*,void*));
bool priority_queue_empty(PriorityQueue* stk);
int priority_queue_size(PriorityQueue* stk);

void priority_queue_clear(PriorityQueue* stk);

void priority_queue_push(PriorityQueue* stk, void* value);
void priority_queue_pop(PriorityQueue* stk);
// return pointer to make it mutable is meaningless.
void* priority_queue_top(PriorityQueue* stk);
