#include <stdbool.h>
#include <stdlib.h>
#define qArray(Template,Size) array_constructor(sizeof(Template),Size);
const int ARRAY_MAX_SIZE = 100;
typedef double ARRAY_TYPE;
// TIPS: re-define the above identifiers
// in *.cpp file to make them shorter
// e.g. const int SIZE = ARRAY_MAX_SIZE;
// e.g. typedef T = ARRAY_TYPE;
// NOTE YOU CAN ONLY DO THAT IN *.cpp FILES

typedef struct Array Array;
// NOTE THAT C has no reference 
// so just ensure the followings works
struct Array{
    void* content;
    int maxlength;
    int step;
};
// array->data[] 

// functions
Array* array_constructor(int step,int maxlength);
ARRAY_TYPE* array_ptr_at(Array* arr);
bool array_empty(Array* arr);
int array_size(Array* arr);
int array_max_size(Array* arr);
