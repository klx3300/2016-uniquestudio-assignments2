#include "rbtree.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "voidutils.h"

rbtreeNode* rbt_constructor(int keyStep,int valueStep){
    rbtreeNode* tmp=malloc(sizeof(rbtreeNode));
    tmp->color=Q_RBTREE_BLACK;
    tmp->lchild=NULL;
    tmp->rchild=NULL;
    tmp->key=NULL;
    tmp->value=NULL;
    tmp->counts=1;
    tmp->keyStep=keyStep;
    tmp->valStep=valueStep;
    tmp->parent=NULL;
    return tmp;
}

rbtreeNode* rbt_rotateLeft(rbtreeNode* center){
    rbtreeNode* tmp=center->rchild;
    rbtreeNode* tparent=center->parent;
    center->rchild=tmp->lchild;
    if(center->rchild!=NULL)
        center->rchild->parent=center;
    tmp->lchild=center;
    center->parent=tmp;
    tmp->color=center->color;
    center->color=Q_RBTREE_RED;
    tmp->counts=center->counts;
    tmp->parent=tparent;
    center->counts=1+rbt_size(center->lchild)+rbt_size(center->rchild);
    return tmp;
}

rbtreeNode* rbt_rotateRight(rbtreeNode* center){
    rbtreeNode* tmp=center->lchild;
    rbtreeNode* tparent=center->parent;
    center->lchild=tmp->rchild;
    if(center->lchild!=NULL)
        center->lchild->parent=center;
    tmp->rchild=center;
    center->parent=tmp;
    tmp->color=center->color;
    center->color=Q_RBTREE_RED;
    tmp->counts=center->counts;
    tmp->parent=tparent;
    center->counts=1+rbt_size(center->lchild)+rbt_size(center->rchild);
    return tmp;
}

void rbt_flipColors(rbtreeNode* parent){
    parent->lchild->color=Q_RBTREE_BLACK;
    parent->rchild->color=Q_RBTREE_BLACK;
    parent->color=Q_RBTREE_RED;
}

bool rbt_isRed(rbtreeNode* node){
    return node->color;
}

int rbt_size(rbtreeNode* node){
    if(node!=NULL)
        return node->counts;
    else
        return 0;
}

void rbt_insert(rbtreeNode** root,void* key,void* value,int (*cmp)(void*,void*)){
    if((*root)->key==NULL){
        (*root)->key=malloc((*root)->keyStep);
        memcpy((*root)->key,key,(*root)->keyStep);
        (*root)->value=malloc((*root)->valStep);
        memcpy((*root)->value,value,(*root)->valStep);
        return;
    }
    (*root)=rbt_put_priv((*root),key,value,(*root)->keyStep,(*root)->valStep,cmp);
    (*root)->color=Q_RBTREE_BLACK;
}

rbtreeNode* rbt_put_priv(rbtreeNode* node,void* key,void* value,int keyStep,int valueStep,int (*cmp)(void*,void*)){
    if(node==NULL){
        rbtreeNode* tmp=rbt_constructor(keyStep,valueStep);
        tmp->color=Q_RBTREE_RED;
        tmp->key=malloc(keyStep);
        memcpy(tmp->key,key,keyStep);
        tmp->value=malloc(valueStep);
        memcpy(tmp->value,value,valueStep);
        return tmp;
    }
    int cmpresult=cmp(key,node->key);
    if(cmpresult<0){
        node->lchild=rbt_put_priv(node->lchild,key,value,keyStep,valueStep,cmp);
        node->lchild->parent=node;
    }else if(cmpresult>0){
        node->rchild=rbt_put_priv(node->rchild,key,value,keyStep,valueStep,cmp);
        node->rchild->parent=node;
    }else
        memcpy(node->value,value,valueStep);
    rbtreeNode* tmp=node;
    if((tmp->rchild!=NULL) && (tmp->lchild!=NULL) && rbt_isRed(tmp->rchild) && !rbt_isRed(tmp->lchild)) tmp=rbt_rotateLeft(tmp);
    if((tmp->lchild!=NULL) && (tmp->lchild->lchild!=NULL) &&rbt_isRed(tmp->lchild) && rbt_isRed(tmp->lchild->lchild)) tmp=rbt_rotateRight(tmp);
    if((tmp->rchild!=NULL) && (tmp->lchild!=NULL) &&rbt_isRed(tmp->lchild) && rbt_isRed(tmp->rchild)) rbt_flipColors(tmp);
    tmp->counts=rbt_size(tmp->lchild)+rbt_size(tmp->rchild)+1;
    return tmp;
}

void rbt_remove(rbtreeNode** root,void* key,int (*cmp)(void*,void*)){
    if(rbt_getValue(*root,key,cmp)==NULL){
        return;
    }
    if(((*root)->lchild)!=NULL && ((*root)->rchild)!=NULL && !rbt_isRed((*root)->lchild) && !rbt_isRed((*root)->rchild))
        (*root)->color=Q_RBTREE_RED;
    (*root)=rbt_remove_priv((*root),key,(*root)->keyStep,cmp);
    if(!((*root)==NULL))
        (*root)->color=Q_RBTREE_BLACK;
}

void rbt_reverseFlipColors(rbtreeNode* parent){
    if(parent==NULL) return;
    if(parent->lchild!=NULL) parent->lchild->color=Q_RBTREE_RED;
    if(parent->rchild!=NULL) parent->rchild->color=Q_RBTREE_RED;
    parent->color=Q_RBTREE_BLACK;

}

rbtreeNode* rbt_moveRedLeft(rbtreeNode* parent){
    rbtreeNode* tmp=parent;
    rbt_reverseFlipColors(parent);
    if(tmp->rchild!=NULL && tmp->rchild->lchild!=NULL && rbt_isRed(parent->rchild->lchild)){
        parent->rchild=rbt_rotateRight(parent->rchild);
        tmp=rbt_rotateLeft(tmp);
    }
    return tmp;
}

rbtreeNode* rbt_moveRedRight(rbtreeNode* parent){
    rbtreeNode* tmp=parent;
    rbt_reverseFlipColors(tmp);
    if(tmp->lchild!=NULL && tmp->lchild->lchild!=NULL && !rbt_isRed(tmp->lchild->lchild)){
        /*parent->lchild=rbt_rotateLeft(parent->lchild);*/
        tmp=rbt_rotateRight(tmp);
    }
    return tmp;
}

rbtreeNode* rbt_getMin(rbtreeNode* node){
    if(node->lchild==NULL)
        return node;
    return node->lchild;
}

void* rbt_getValue(rbtreeNode* node,void* key,int (*cmp)(void*,void*)){
    if(node==NULL){
        return NULL;
    }
    /*printf("comparing %d with %d\n",*((int*)key),*((int*)node->key));*/
    int cmpresult=cmp(key,node->key);
    if(cmpresult<0)
        return rbt_getValue(node->lchild,key,cmp);
    else if(cmpresult>0)
        return rbt_getValue(node->rchild,key,cmp);
    else
        return node->value;
}

rbtreeNode* rbt_balance(rbtreeNode* node){
    rbtreeNode* tmp=node;
    if(node==NULL)
        return NULL;
    if(tmp->rchild!=NULL && rbt_isRed(tmp->rchild))
        tmp=rbt_rotateLeft(tmp);
    if(tmp->lchild!=NULL && tmp->lchild->lchild!=NULL && rbt_isRed(tmp->lchild) && rbt_isRed(tmp->lchild->lchild))
        tmp=rbt_rotateRight(tmp);
    if(tmp->lchild!=NULL && tmp->rchild!=NULL && rbt_isRed(tmp->lchild) && rbt_isRed(tmp->rchild))
        rbt_flipColors(tmp);
    tmp->counts=rbt_size(tmp->lchild)+rbt_size(tmp->rchild)+1;
    
    return tmp;
}

rbtreeNode* rbt_removeMin(rbtreeNode* node){
    rbtreeNode* tmp=node;
    if(node->lchild==NULL)
        return NULL;
    if(tmp->lchild!=NULL && tmp->lchild->lchild!=NULL && !rbt_isRed(tmp->lchild) && !rbt_isRed(tmp->lchild->lchild))
        tmp=rbt_moveRedLeft(tmp);
    rbtreeNode* tmptr=rbt_removeMin(tmp->lchild);
    if(tmptr==NULL){
        free(tmp->lchild->key);
        free(tmp->lchild->value);
        free(tmp->lchild);
    }
    tmp->lchild=tmptr;
    return rbt_balance(tmp);
}

rbtreeNode* rbt_remove_priv(rbtreeNode* node,void* key,int keyStep,int (*cmp)(void*,void*)){
    rbtreeNode* tmp=node;
    int k=*(int*)key;
    /*printf("TARGET:%d\n",*(int*)node->key);*/
    if(cmp(key,tmp->key)<0){
        if(tmp->lchild!=NULL && tmp->lchild->lchild!=NULL && !rbt_isRed(tmp->lchild) && !rbt_isRed(tmp->lchild->lchild))
            tmp=rbt_moveRedLeft(tmp);
        rbtreeNode* tmptr=rbt_remove_priv(tmp->lchild,key,keyStep,cmp);
        if(tmp!=NULL && tmptr==NULL){
            free(tmp->lchild->key);
            free(tmp->lchild->value);
            free(tmp->lchild);
        }
        tmp->lchild=tmptr;
    }else{
        if(tmp->lchild!=NULL && rbt_isRed(tmp->lchild))
            tmp=rbt_rotateRight(tmp);
        if(tmp->rchild!=NULL && tmp->rchild->lchild!=NULL && !rbt_isRed(tmp->rchild) && !rbt_isRed(tmp->rchild->lchild))
            tmp=rbt_moveRedRight(tmp);
        if(cmp(key,tmp->key)==0){
            if(tmp->rchild!=NULL){
                memcpy(tmp->value,rbt_getValue(tmp->rchild,(rbt_getMin(tmp->rchild))->key,cmp),tmp->valStep);
                memcpy(tmp->key,rbt_getMin(tmp->rchild)->key,keyStep);
                rbtreeNode* tmptr=rbt_removeMin(tmp->rchild);
                if(tmp!=NULL && tmptr==NULL){
                    free(tmp->rchild->key);
                    free(tmp->rchild->value);
                    free(tmp->rchild);
                }
                tmp->rchild=tmptr;
            }else if(tmp->lchild!=NULL){
                memcpy(tmp->value,tmp->lchild->value,tmp->valStep);
                memcpy(tmp->key,tmp->lchild->key,tmp->keyStep);
                rbtreeNode* tmptr=tmp->lchild;
                tmp->lchild=tmptr->lchild;
                tmp->rchild=tmptr->rchild;
                if(tmp->lchild!=NULL) tmp->lchild->parent=tmp;
                if(tmp->rchild!=NULL) tmp->rchild->parent=tmp;
                free(tmptr->key);
                free(tmptr->value);
                free(tmptr);
            }else{
                return NULL;
            }
        }else{
            if(tmp->rchild==NULL)
                return NULL;
            rbtreeNode* tmptr=rbt_remove_priv(tmp->rchild,key,keyStep,cmp);
            if(tmp!=NULL && tmptr==NULL){
                free(tmp->rchild->key);
                free(tmp->rchild->value);
                free(tmp->rchild);
            }
            tmp->rchild=tmptr;
        }
    }
    return rbt_balance(tmp);
}

rbtreeIterator* rbtreeIterator_constructor(rbtreeNode* root){
    rbtreeIterator* tmp=malloc(sizeof(rbtreeIterator));
    tmp->current=root;
    return tmp;
}

void rbtreeIterator_increase(rbtreeIterator* this){
    if(this->current->rchild==NULL){
        if(this->current->parent==NULL){
            this->current=NULL;
            return;
        }
        if(this->current->parent->rchild==this->current){
            while(this->current->parent->rchild==this->current){
                this->current=this->current->parent;
                if(this->current->parent==NULL){
                    this->current=NULL;
                    return;
                }
            }
            this->current=this->current->parent;
        }else{
            this->current=this->current->parent;
        }
    }else{
        this->current=this->current->rchild;
        while(this->current->lchild!=NULL)
            this->current=this->current->lchild;
    }
}

void rbtreeIterator_decrease(rbtreeIterator* this){
    if(this->current->lchild==NULL){
        if(this->current->parent==NULL){
            this->current=NULL;
            return;
        }
        if(this->current->parent->lchild==this->current){
            while(this->current->parent->lchild==this->current){
                this->current=this->current->parent;
                if(this->current->parent==NULL){
                    this->current=NULL;
                    return;
                }
            }
            this->current=this->current->parent;
        }else{
            this->current=this->current->parent;
        }
    }else{
        this->current=this->current->lchild;
        while(this->current->rchild!=NULL)
            this->current=this->current->rchild;
    }
}

rbtreeIterator* rbt_first(rbtreeNode* root){
    rbtreeIterator *p=rbtreeIterator_constructor(root);
    while(p->current->lchild!=NULL)
        p->current=p->current->lchild;
    return p;
}

rbtreeIterator* rbt_last(rbtreeNode* root){
    rbtreeIterator *p=rbtreeIterator_constructor(root);
    while(p->current->rchild!=NULL)
        p->current=p->current->rchild;
    return p;
}

rbtreeIterator* rbt_find(rbtreeNode* root,void* key,int (*cmp)(void*,void*)){
    return rbtreeIterator_constructor(rbt_getValue(root,key,cmp));
}

rbtreeIterator* rbt_getNext(rbtreeNode* root,void* key,int (*cmp)(void*,void*)){
    rbtreeIterator* i=rbt_find(root,key,cmp);
    rbtreeIterator_increase(i);
    return i;
}

rbtreeIterator* rbt_getPrev(rbtreeNode* root,void* key,int (*cmp)(void*,void*)){
    rbtreeIterator* i=rbt_find(root,key,cmp);
    rbtreeIterator_decrease(i);
    return i;
}

void rbt_clear(rbtreeNode* current){
    free(current->value);
    free(current->key);
    if(current->lchild!=NULL)
        rbt_clear(current->lchild);
    if(current->rchild!=NULL)
        rbt_clear(current->rchild);
    free(current);
}
