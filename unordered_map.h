#ifndef Q_LIST_H
#include "list.h"
#endif
#include <stdbool.h>
#include <stdlib.h>
#define qUnorderedMap(keyType,valueType,hashfunc,arrayLength) unordered_map_constructor(sizeof(keyType),sizeof(valueType),hashfunc,arrayLength)
typedef struct Unordered_map Unordered_map;
typedef long long UNORDERED_MAP_KEY;
typedef double UNORDERED_MAP_TYPE;

#define Q_DEFAULT_MAXHASHV 131

typedef struct MapData{
    void* key;
    void* value;
    int keyStep;
    int valueStep;
}MapData;

struct Unordered_map{
    List** listArray;
    int keyStep;
    int valueStep;
    unsigned int (*hashfunc)(void*);
    unsigned int maxlength;
    unsigned int counts;
};
// functions 
// note the absence of reference
Unordered_map* unordered_map_constructor(int keyStep,int valueStep,unsigned int (*hashfunc)(void*),unsigned int maxhashv);
MapData* map_data_constructor(Unordered_map* which,void* key,void* value);
bool unordered_map_empty(Unordered_map* st);
unsigned int unordered_map_size(Unordered_map* st);

void unordered_map_clear(Unordered_map* st);

void unordered_map_insert(Unordered_map* st, void* key, void* value);
void unordered_map_earse(Unordered_map* st, void* key);

// return NULL if not found
// otherwise return pointer to value 
void* unordered_map_ptr_at(Unordered_map* st, void* key);

int hash_int(void*);
int hash_float(void*);
int hash_double(void*);
int hash_long(void*);
int hash_long_long(void*);
