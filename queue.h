#include <stdbool.h>
#include <stdlib.h>
#ifndef Q_LIST_H
#include "list.h"
#endif
#define qQueue(Template) queue_constructor(sizeof(Template))
typedef double QUEUE_TYPE;
// TIPS: re-define the above identifiers
// in *.cpp file to make them shorter
// e.g. typedef T = QUEUE_TYPE;
// NOTE YOU CAN ONLY DO THAT IN *.cpp FILES

typedef struct Queue Queue;

struct Queue{
    List *l;
};
// functions 
// note the absence of reference
Queue* queue_constructor(int stepLength);
bool queue_empty(Queue* que);
int queue_size(Queue* que);

void queue_clear(Queue* que);

void queue_push(Queue* que,void* value);
void queue_pop(Queue* que);
void* queue_top(Queue* que);
