
#include <stdbool.h>
#include <stdlib.h>
#include "rbtree.h"
typedef struct Set Set;
typedef struct SetIterator SetIterator;

typedef double SET_TYPE;

#define qSet(KeyType,ValueType,Comparator) set_constructor(sizeof(KeyType),sizeof(ValueType),Comparator);

struct Set{
    rbtreeNode* root;
    int (*cmp)(void*,void*);
};

struct SetIterator{
    rbtreeIterator* ptr;
    int (*cmp)(void*,void*);
};

// functions 
// note the absence of reference
Set* set_constructor(int keyStep,int valStep,int (*cmp)(void*,void*));
bool set_empty(Set* st);
int set_size(Set* st);

void set_clear(Set* st);

void set_insert(Set* st, void* key,void* value);
void set_erase(Set* st, void* key);


SetIterator* set_begin(Set* st);
SetIterator* set_end(Set* st);
SetIterator* set_find(Set* st, void* key);
SetIterator* set_lower_bound(Set* st, void* key);
SetIterator* set_upper_bound(Set* st, void* key);


void SetIterator_self_increase(SetIterator* pIter);
void SetIterator_self_decrease(SetIterator* pIter);

// iterators is of the same location.
bool SetIterator_equal(SetIterator* iter_a, SetIterator* iter_b);
bool SetIterator_not_equal(SetIterator* iter_a, SetIterator* iter_b);

const void* set_get_data_ptr(SetIterator* iter);
