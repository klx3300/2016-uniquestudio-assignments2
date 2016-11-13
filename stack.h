#include <stdbool.h>
#include <stdlib.h>
typedef double STACK_TYPE;
// TIPS: re-define the above identifiers
// in *.cpp file to make them shorter
// e.g. typedef T = STACK_TYPE;
// NOTE YOU CAN ONLY DO THAT IN *.cpp FILES

typedef struct Stack Stack;

// functions 
// note the absence of reference
bool stack_empty(Stack* vec);
int stack_size(Stack* vec);
int stack_capacity(Stack* vec);

void stack_reserve(Stack* vec, int new_cap);
void stack_shrink_to_fit(Stack* vec);
void stack_clear(Stack* vec);

void stack_push(Stack* vec, STACK_TYPE value);
void stack_pop(Stack* vec);
