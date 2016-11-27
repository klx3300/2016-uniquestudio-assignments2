#include "set.h"
#include <string.h>

Set* set_constructor(int keyStep,int valStep,int (*cmp)(void*,void*)){
    Set* s=malloc(sizeof(Set));
    s->root=rbt_constructor(keyStep,valStep);
    s->smallest=malloc(sizeof(SetIterator));
    s->smallest->ptr=rbtreeIterator_constructor(s->root);
    s->smallest->cmp=cmp;
    s->largest=malloc(sizeof(SetIterator));
    s->largest->ptr=rbtreeIterator_constructor(s->root);
    s->largest->cmp=cmp;
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
    free(this->smallest);
    free(this->largest);
    this->root=rbt_constructor(keyStep,valStep);

    this->smallest=malloc(sizeof(SetIterator));
    this->smallest->ptr=rbtreeIterator_constructor(this->root);
    this->smallest->cmp=this->cmp;
    this->largest=malloc(sizeof(SetIterator));
    this->largest->ptr=rbtreeIterator_constructor(this->root);
    this->largest->cmp=this->cmp;
}

void set_insert(Set* this,void* key,void* value){
    if(this->smallest->ptr->current->key==NULL){
        // init
        this->smallest->ptr->current->key=malloc(this->root->keyStep);
        memcpy(this->smallest->ptr->current->key,key,this->root->keyStep);
        this->smallest->ptr->current->value=malloc(this->root->valStep);
        memcpy(this->smallest->ptr->current->value,value,this->root->valStep);
    }
    if(this->largest->ptr->current->key==NULL){
        // init
        this->largest->ptr->current->key=malloc(this->root->keyStep);
        memcpy(this->largest->ptr->current->key,key,this->root->keyStep);
        this->largest->ptr->current->value=malloc(this->root->valStep);
        memcpy(this->largest->ptr->current->value,value,this->root->valStep);
    }

    rbt_insert(&this->root,key,value,this->cmp);
    if(this->cmp(this->smallest->ptr->current->key,key)>0){
        SetIterator_self_decrease(this->smallest);
    }
    if(this->cmp(this->largest->ptr->current->key,key)<0){
        SetIterator_self_increase(this->largest);
    }
    
}

void set_erase(Set* this,void* key){
    
    if(this->cmp(this->smallest->ptr->current->key,key)==0){
        SetIterator_self_increase(this->smallest);
    }
    if(this->cmp(this->largest->ptr->current->key,key)==0){
        SetIterator_self_decrease(this->largest);
    }
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

