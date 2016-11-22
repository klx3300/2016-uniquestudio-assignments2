#include "rbtree.h"
#include <string.h>
#include <stdlib.h>

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
    return tmp;
}

rbtreeNode* rbt_rotateLeft(rbtreeNode* center){
    rbtreeNode* tmp=center->rchild;
    center->rchild=tmp->lchild;
    tmp->lchild=center;
    tmp->color=center->color;
    center->color=Q_RBTREE_RED;
    tmp->counts=center->counts;
    center->counts=1+rbt_size(center->lchild)+rbt_size(center->rchild);
    return tmp;
}

rbtreeNode* rbt_rotateRight(rbtreeNode* center){
    rbtreeNode* tmp=center->lchild;
    center->lchild=tmp->rchild;
    tmp->rchild=center;
    tmp->color=center->color;
    center->color=Q_RBTREE_RED;
    tmp->counts=center->counts;
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
    return node->counts;
}

void rbt_insert(rbtreeNode** root,void* key,void* value,int (*cmp)(void*,void*)){
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
    if(cmpresult<0)
        node->lchild=rbt_put_priv(node->lchild,key,value,keyStep,valueStep,cmp);
    else if(cmpresult>0)
        node->rchild=rbt_put_priv(node->rchild,key,value,keyStep,valueStep,cmp);
    else
        memcpy(node->value,value,valueStep);
    rbtreeNode* tmp=node;
    if(rbt_isRed(tmp->rchild) && !rbt_isRed(tmp->lchild)) tmp=rbt_rotateLeft(tmp);
    if(rbt_isRed(tmp->lchild) && rbt_isRed(tmp->lchild->lchild)) tmp=rbt_rotateRight(tmp);
    if(rbt_isRed(tmp->lchild) && rbt_isRed(tmp->rchild)) rbt_flipColors(tmp);
    tmp->counts=rbt_size(tmp->lchild)+rbt_size(tmp->rchild)+1;
    return tmp;
}

void rbt_remove(rbtreeNode** root,void* key,int (*cmp)(void*,void*)){
    if(!rbt_isRed((*root)->lchild) && !rbt_isRed((*root)->rchild))
        (*root)->color=Q_RBTREE_RED;
    (*root)=rbt_remove_priv((*root),key,(*root)->keyStep,cmp);
    if(!((*root)==NULL))
        (*root)->color=Q_RBTREE_BLACK;
}

void rbt_reverseFlipColors(rbtreeNode* parent){
    parent->lchild->color=Q_RBTREE_RED;
    parent->rchild->color=Q_RBTREE_RED;
    parent->color=Q_RBTREE_BLACK;

}

rbtreeNode* rbt_moveRedLeft(rbtreeNode* parent){
    rbtreeNode* tmp=parent;
    rbt_reverseFlipColors(parent);
    if(rbt_isRed(parent->rchild->lchild)){
        parent->rchild=rbt_rotateRight(parent->rchild);
        tmp=rbt_rotateLeft(tmp);
    }
    return tmp;
}

rbtreeNode* rbt_moveRedRight(rbtreeNode* parent){
    rbtreeNode* tmp=parent;
    rbt_reverseFlipColors(tmp);
    if(!rbt_isRed(tmp->lchild->lchild))
        tmp=rbt_rotateRight(tmp);
    return tmp;
}

rbtreeNode* rbt_getMin(rbtreeNode* node){
    if(node->lchild==NULL)
        return node;
    return node->lchild;
}

void* rbt_getValue(rbtreeNode* node,void* key,int (*cmp)(void*,void*)){
    if(node==NULL)
        return NULL;
    int cmpresult=cmp(key,node->key);
    if(cmp<0)
        return rbt_getValue(node->lchild,key,cmp);
    else if(cmp>0)
        return rbt_getValue(node->rchild,key,cmp);
    else
        return node->value;
}

rbtreeNode* rbt_balance(rbtreeNode* node){
    rbtreeNode* tmp=node;
    if(rbt_isRed(tmp->rchild))
        tmp=rbt_rotateLeft(tmp);
    if(rbt_isRed(tmp->lchild) && rbt_isRed(tmp->lchild->lchild))
        tmp=rbt_rotateRight(tmp);
    if(rbt_isRed(tmp->lchild) && rbt_isRed(tmp->rchild))
        rbt_flipColors(tmp);
    tmp->counts=rbt_size(tmp->lchild)+rbt_size(tmp->rchild)+1;
    return tmp;
}

rbtreeNode* rbt_removeMin(rbtreeNode* node){
    rbtreeNode* tmp=node;
    if(node->lchild==NULL)
        return NULL;
    if(!rbt_isRed(tmp->lchild) && !rbt_isRed(tmp->lchild->lchild))
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
    if(cmp(key,tmp->key)<0){
        if(!rbt_isRed(tmp->lchild) && !rbt_isRed(tmp->lchild->lchild))
            tmp=rbt_moveRedLeft(tmp);
        rbtreeNode* tmptr=rbt_remove_priv(tmp->lchild,key,keyStep,cmp);
        if(tmptr==NULL){
            free(tmp->lchild->key);
            free(tmp->lchild->value);
            free(tmp->lchild);
        }
        tmp->lchild=tmptr;
    }else{
        if(rbt_isRed(tmp->lchild))
            tmp=rbt_rotateRight(tmp);
        if(cmp(key,tmp->key)==0 && (tmp->rchild == NULL))
            return NULL;
        if(!rbt_isRed(tmp->rchild) && !rbt_isRed(tmp->rchild->lchild))
            tmp=rbt_moveRedRight(tmp);
        if(cmp(key,tmp->key)==0){
            memcpy(tmp->value,rbt_getValue(tmp->rchild,(rbt_getMin(tmp->rchild))->key,cmp),tmp->valStep);
            memcpy(tmp->key,rbt_getMin(tmp->rchild)->key,keyStep);
            rbtreeNode* tmptr=rbt_removeMin(tmp->rchild);
            if(tmptr==NULL){
                free(tmp->rchild->key);
                free(tmp->lchild->value);
                free(tmp->lchild);
            }
            tmp->rchild=tmptr;
        }else{
            rbtreeNode* tmptr=rbt_remove_priv(tmp->rchild,key,keyStep,cmp);
            if(tmptr==NULL){
                free(tmp->rchild->key);
                free(tmp->rchild->value);
                free(tmp->rchild);
            }
            tmp->rchild=tmptr;
        }
    }
    return rbt_balance(tmp);
}
