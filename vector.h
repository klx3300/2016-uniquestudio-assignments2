#include <stdbool.h>
#include <stdlib.h>
#define qVector(Template) vector_constructor(sizeof(Template));
typedef double VECTOR_TYPE;
// TIPS: re-define the above identifiers
// in *.cpp file to make them shorter
// e.g. typedef T = VECTOR_TYPE;
// NOTE YOU CAN ONLY DO THAT IN *.cpp FILES

struct Vector{
    void *arr;
    int counts;
    int size;
    int step;
};

typedef struct Vector Vector;
typedef struct VectorIterator VectorIterator;
// NOTE THAT C has no reference 
// so just ensure the followings works

/*
vector->data[] 
*/

// functions 
// note the absence of reference
Vector* vector_constructor(int stepLength);
void* vector_ptr_at(Vector* vec);
bool vector_empty(Vector* vec);
int vector_size(Vector* vec);
int vector_capacity(Vector* vec);

void vector_reserve(Vector* vec, int capacity);
void vector_resize(Vector* vec, int new_size);
void vector_shrink_to_fit(Vector* vec);
void vector_clear(Vector* vec);
// wasting time below
// skip these 4 commented lines
// VectorIterator vector_begin(Vector* vec);
// VectorIterator vector_end(Vector* vec);
// void increse(VectorIterator* pIter);
// void decrease(VectorIterator* pIter);


//      a, b, c, ...,m, where, n, ...
// =>   a, b, c, ...,m, value, where, n, ...
// 'where' could be end()
void vector_insert(Vector* vec, int where, void* value);

void vector_erase(Vector* vec, int where);


void vector_push_back(Vector* vec, void* value);
void vector_pop_back(Vector* vec);
