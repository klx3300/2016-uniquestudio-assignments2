#include"vector.h"
#include"voidutils.h"
#include<string.h>

Vector* vector_constructor(int stepLength){
    Vector* v=malloc(sizeof(Vector));
    v->arr=NULL;
    v->counts=0;
    v->size=0;
    v->step=stepLength;
    return v;
}

void *vector_ptr_at(Vector* vec){
    return vec->arr;
}

bool vector_empty(Vector* vec){
    return vec->counts;
}

int vector_size(Vector* vec){
    return vec->counts;
}

int vector_capacity(Vector* vec){
    return vec->size;
}

void vector_resize(Vector* vec,int new_size){
    if(new_size<vec->counts){
        fakeSegmentFault("Bad combination of operator and operands.");
    }
    if(new_size==0){
        free(vec->arr);
        vec->arr=NULL;
        vec->size=0;
        return;
    }
    void* newarr=malloc(vec->step*new_size);
    void* origiterator=vec->arr,*newiterator=newarr;
    for(int i=0;i<vec->counts;i++){
        (*(char*)newiterator)=(*(char*)origiterator);
        nextStep(&newiterator,vec->step);nextStep(&origiterator,vec->step);
    }
    vec->size=new_size;
    if(vec->arr!=NULL)
        free(vec->arr);
    vec->arr=newarr;
}

void vector_reserve(Vector* vec,int capacity){
    if(capacity*2<vec->size)
        return;
    vector_resize(vec,capacity*2);
}
// Warning:
// Due to the resizing ,next insertion will cost up to O(n)
void vector_shrink_to_fit(Vector* vec){
    vector_resize(vec,vec->counts);
}

void vector_clear(Vector *vec){
    free(vec->arr);
    vec->arr=NULL;
    vec->counts=0;vec->size=0;
}

void vector_insert(Vector* vec,int where,void* value){
    if(vec->size==0){
        vec->size=1;
        vec->arr=malloc(vec->step);
    }
    if((++(vec->counts))>vec->size){
        //RESIZE TO 2 TIMES.
        vector_resize(vec,vec->size*2);
    }
    if(vec->counts-where-1>0)
        memmove((vec->arr+(where*vec->step)),(vec->arr+((where+1)*vec->step)),(vec->counts-where-1)*vec->step);
    memcpy((vec->arr+(where*vec->step)),value,vec->step);
}

void vector_erase(Vector* vec,int where){
    if(vec->arr==NULL || vec->counts==0){
        fakeSegmentFault("Address Boundary Error.");
    }
    if((--(vec->counts))<=vec->size/4){
        //RESIZE to HALF
        vector_resize(vec,vec->size/2);
    }
    if(vec->arr==NULL)
        return;
    memmove((vec->arr+((where+1)*vec->step)),(vec->arr+(where*vec->step)),(vec->counts-where)*vec->step);
    memset((vec->arr+(vec->counts*vec->step)),0,vec->step);
}

void vector_push_back(Vector* vec,void* value){
    if(vec->size==0){
        vec->size=1;
        vec->arr=malloc(vec->step);
    }
    if((++(vec->counts))>vec->size){
        //RESIZE TO 2 TIMES.
        vector_resize(vec,vec->size*2);
    }
    memcpy(vec->arr+((vec->counts-1)*vec->step),value,vec->step);
}

void vector_pop_back(Vector* vec){
    if(vec->arr==NULL || vec->counts==0){
        fakeSegmentFault("Address Boundary Error.");
    }
    if((vec->counts)--<=vec->size/4){
        vector_resize(vec,vec->size/4);
    }
    if(vec->arr==NULL)
        return;
    memset(vec->arr+(vec->counts*vec->step),0,vec->step);
}
