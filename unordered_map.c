#include "unordered_map.h"
#include <string.h>

Unordered_map* Unordered_map_constructor(int keyStep,int valueStep,unsigned int (*hashfunc)(void*),unsigned int maxhashv){
    Unordered_map* this=malloc(sizeof(Unordered_map));
    this->keyStep=keyStep;
    this->valueStep=valueStep;
    this->hashfunc=hashfunc;
    this->maxlength=maxhashv;
    this->counts=0;
    this->listArray=malloc(sizeof(List*)*maxhashv);
    for(unsigned int iter=0;iter<maxhashv;iter++){
        (this->listArray)[iter]=qList(MapData);
    }
    return this;
}

MapData* map_data_constructor(Unordered_map* this,void* key,void* value){
    MapData* ptr=malloc(sizeof(MapData));
    ptr->keyStep=this->keyStep;
    ptr->valueStep=this->valueStep;
    ptr->key=malloc(this->keyStep);
    memcpy(ptr->key,key,this->keyStep);
    ptr->value=malloc(this->valueStep);
    memcpy(ptr->value,value,this->valueStep);
    return ptr;
}

bool unordered_map_empty(Unordered_map* this){
    return this->counts;
}

unsigned int unordered_map_size(Unordered_map* this){
    return this->counts;
}

void unordered_map_clear(Unordered_map* this){
    for(unsigned int iter=0;iter<this->maxlength;iter++){
        if(list_empty((this->listArray)[iter]))
            continue;
        list_clear((this->listArray)[iter]);
    }
}

void unordered_map_insert(Unordered_map* this,void* key,void* value){
    unsigned int hashv=this->hashfunc(key);
    List* referred_list=(this->listArray)[hashv];
    for(ListIterator iter=list_begin(referred_list);iter.curr!=NULL;ListIterator_self_increase(&iter)){
            if(!memcmp(((MapData*)(iter.curr->ptr))->key,key,this->keyStep)){
                memcpy(((MapData*)(iter.curr->ptr))->value,value,this->valueStep);
                return;
            }
    }
    list_push_back(referred_list,map_data_constructor(this,key,value));
}

void unordered_map_erase(Unordered_map* this,void* key){
    unsigned int hashv=this->hashfunc(key);
    List* referred_list=(this->listArray)[hashv];
    for(ListIterator iter=list_begin(referred_list);iter.curr!=NULL;ListIterator_self_increase(&iter)){
        if(!memcmp(((MapData*)(iter.curr->ptr))->key,key,this->keyStep)){
            ListNode* prev=iter.curr->prev;
            ListNode* next=iter.curr->next;
            ListNode* curr=iter.curr;
            free(curr->ptr);
            prev->next=next;
            next->prev=prev;
            free(curr);
            referred_list->size--;
            return;
        }
    }
}

void* unordered_map_ptr_at(Unordered_map* this,void* key){
    unsigned int hashv=this->hashfunc(key);
    List* referred_list=(this->listArray)[hashv];
    for(ListIterator iter=list_begin(referred_list);iter.curr!=NULL;ListIterator_self_increase(&iter)){
        if(!memcmp(((MapData*)(iter.curr->ptr))->key,key,this->keyStep)){
            return ((MapData*)(iter.curr->ptr))->value;
        }
    }
    return NULL;
}
