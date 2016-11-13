
#include <stdbool.h>
#include <stdlib.h>
typedef struct Set Set;
typedef struct SetIterator SetIterator;

typedef double SET_TYPE;


// functions 
// note the absence of reference
bool set_empty(Set* lis);
int set_size(Set* lis);

void set_clear(Set* lis);

//      a, b, c, ...,m, where, n, ...
// =>   a, b, c, ...,m, value, where, n, ...
void set_insert(Set* lis, SET_TYPE value);
void set_earse(Set* lis, SET_TYPE value);


SetIterator set_begin(Set* lis);
SetIterator set_end(Set* lis);
void increse(SetIterator* pIter);
void decrease(SetIterator* pIter);

bool SetIterator_equal(SetIterator iter_a, SetIterator iter_b);
bool SetIterator_not_equal(SetIterator iter_a, SetIterator iter_b);

// something like derefence
// you have to write like:
// ---------------------------------------
// SET_TYPE value;
// *set_get_data_ptr(some_iter) = value;
// ---------------------------------------
SET_TYPE* set_get_data_ptr(SetIterator* iter);
