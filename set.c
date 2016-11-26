#include "set.h"

Set* set_constructor(int keyStep,int valStep,int (*cmp)(void*,void*)){
    Set* s=malloc(sizeof(Set));
    s->root=rbt_constructor(keyStep,valStep);
    s->cmp=cmp;
    return s;
}

bool set_empty(Set* this){
    return !rbt_size(this->root);
}

int set_size(Set* this){
    return rbt_size(this->root);
}

void set_clear(Set* this){
    int keyStep=this->root->keyStep,valStep=this->root->valStep;
    rbt_clear(this->root);
    this->root=rbt_constructor(keyStep,valStep);
}

void set_insert(Set* this,void* key,void* value){
    rbt_insert(&this->root,key,value,this->cmp);
}

void set_erase(Set* this,void* key){
    rbt_remove(&this->root,key,this->cmp);
}

SetIterator* set_begin(Set* st){
    SetIterator* siter=malloc(sizeof(SetIterator));
    siter->ptr=rbt_first(st->root);
    siter->cmp=st->cmp;
    return siter;
}

SetIterator* set_end(Set* st){
    SetIterator* siter=malloc(sizeof(SetIterator));
    siter->ptr=rbt_last(st->root);
    siter->cmp=st->cmp;
    return siter;
}

SetIterator* set_find(Set* st,void* key){
    SetIterator* siter=malloc(sizeof(SetIterator));
    siter->ptr=rbt_find(st->root,key,st->cmp);
    siter->cmp=st->cmp;
    return siter;
}

SetIterator* set_lower_bound(Set* st,void* key){
    SetIterator* siter=malloc(sizeof(SetIterator));
    siter->ptr=rbt_getNext(st->root,key,st->cmp);
    siter->cmp=st->cmp;
    return siter;
}

SetIterator* set_upper_bound(Set* st,void* key){
    SetIterator* siter=malloc(sizeof(SetIterator));
    siter->ptr=rbt_getPrev(st->root,key,st->cmp);
    siter->cmp=st->cmp;
    return siter;
}

void SetIterator_self_increase(SetIterator* this){
    rbtreeIterator_increase(this->ptr);
}

void SetIterator_self_decrease(SetIterator* this){
    rbtreeIterator_decrease(this->ptr);
}

bool SetIterator_equal(SetIterator* a,SetIterator* b){
    return a->ptr->current==b->ptr->current;
}

bool SetIterator_not_equal(SetIterator* a,SetIterator* b){
    return !SetIterator_equal(a,b);
}

const void* set_get_data_ptr(SetIterator* iter){
    return iter->ptr->current->value;
}

