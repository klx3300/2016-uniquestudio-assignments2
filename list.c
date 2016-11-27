#include "list.h"
#include <string.h>
#include "voidutils.h"

void* list_ptr_at(List* lst){
    return lst->first;
}

List* list_constructor(int stepLength){
    List* tmpl=malloc(sizeof(List));
    tmpl->first=NULL;
    tmpl->last=NULL;
    tmpl->step=stepLength;
    tmpl->size=0;
    return tmpl;
}

ListNode* listNode_constructor(int stepLength){
    ListNode* tmpln=malloc(sizeof(ListNode));
    tmpln->ptr=NULL;
    tmpln->step=stepLength;
    tmpln->prev=NULL;
    tmpln->next=NULL;
    return tmpln;
}

ListIterator* listIterator_constructor(int stepLength){
    ListIterator* iter=malloc(sizeof(ListIterator));
    iter->step=stepLength;
    iter->curr=NULL;
    return iter;
}

bool list_empty(List* lst){
    return !lst->size;
}

int list_size(List* lst){
    return lst->size;
}

void list_clear(List* lst){
    ListNode* iterator=lst->last;
    for(;iterator->prev!=NULL;iterator=iterator->prev){
        free(iterator->ptr);
        if(iterator->next!=NULL)
            free(iterator->next);

    }
    free(iterator->ptr);
    free(iterator);
    lst->first=NULL;lst->last=NULL;lst->size=0;
}

void list_insert(List* lst,ListIterator* where,void* value){
    if(lst->first==NULL){
        list_push_back(lst,value);
        return;
    }
    ListNode* iterator=where->curr;
    ListNode* prev=iterator->prev;
    ListNode* tmp=listNode_constructor(lst->step);
    prev->next=tmp;
    tmp->prev=prev;
    tmp->next=iterator;
    iterator->prev=tmp;
    tmp->ptr=malloc(lst->step);
    memcpy(tmp->ptr,value,lst->step);
    lst->size++;
}

void list_push_back(List* lst,void* value){
    ListNode* tmp=listNode_constructor(lst->size);
    tmp->prev=lst->last;
    if(lst->last!=NULL)
        lst->last->next=tmp;
    else{
        lst->first=tmp;
    }
    lst->last=tmp;
    tmp->ptr=malloc(lst->step);
    memcpy(tmp->ptr,value,lst->step);
    lst->size++;
}

void list_pop_back(List* lst){
    if(lst->size==0){
        fakeSegmentFault("Address Boundary Error.");
    }
    free(lst->last->ptr);
    if(lst->first==lst->last){
        free(lst->last);
        lst->first=NULL;lst->last=NULL;
    }else{
        ListNode *tmptr=lst->last->prev;
        free(lst->last);
        lst->last=tmptr;
        lst->last->next=NULL;
    }
    lst->size--;
}

void list_push_front(List* lst,void* value){
    if(lst->size==0){
        list_push_back(lst,value);
        return;
    }
    ListNode* first=lst->first;
    ListNode* tmp=listNode_constructor(lst->step);
    tmp->next=first;
    first->prev=tmp;
    lst->first=tmp;
    tmp->ptr=malloc(lst->step);
    memcpy(tmp->ptr,value,lst->step);
    lst->size++;
}

void list_pop_front(List* lst){
    if(lst->size==0){
        fakeSegmentFault("Address Boundary Error.");

    }
    lst->size--;
    free(lst->first->ptr);
    if(lst->first==lst->last){
        lst->last=NULL;
    }
    ListNode* first=lst->first;
    lst->first=first->next;
    if(lst->first->next!=NULL)
        lst->first->next->prev=NULL;
    free(first);
}

void list_erase(List* lst,ListIterator* where){
    if(lst->size==0){
        fakeSegmentFault("Address Boundary Error.");

    }
    ListNode* iterator=where->curr;
    if(iterator==NULL){
        fakeSegmentFault("Address Boundary Error.");

    }
    if(lst->first==lst->last){
        list_pop_back(lst);
        return;
    }
    free(iterator->ptr);
    ListNode *prev=iterator->prev,*next=iterator->next;
    if(prev!=NULL)
        prev->next=next;
    if(next!=NULL)
        next->prev=prev;
    free(iterator);
    lst->size--;
}

ListIterator list_begin(List* lst){
    ListIterator iterator;
    iterator.step=lst->step;
    iterator.FLAG_TYPE=ITERATOR_TYPE_NORMAL;
    iterator.curr=lst->first;
    return iterator;
}

ListIterator list_end(List* lst){
    ListIterator iterator=list_begin(lst);
    iterator.curr=lst->last;
    return iterator;
}

void ListIterator_self_increase(ListIterator* iterator){
    switch(iterator->FLAG_TYPE){
        case ITERATOR_TYPE_NORMAL:
            iterator->curr=iterator->curr->next;
            break;
        case ITERATOR_TYPE_REVERSE:
            iterator->curr=iterator->curr->prev;
            break;
        default:
            iterator->curr=iterator->curr->next;

    }
}

void ListIterator_self_decrease(ListIterator* iterator){
    switch(iterator->FLAG_TYPE){

        case ITERATOR_TYPE_NORMAL:
            iterator->curr=iterator->curr->prev;
            break;
        case ITERATOR_TYPE_REVERSE:
            iterator->curr=iterator->curr->next;
            break;
        default:
            iterator->curr=iterator->curr->prev;

    }
}

bool ListIterator_equal(ListIterator a,ListIterator b){
    return a.curr==b.curr;
}

bool ListIterator_not_equal(ListIterator a,ListIterator b){
    return !ListIterator_equal(a,b);
}

void* list_get_data_ptr(ListIterator* iterator){
    return iterator->curr;
}
