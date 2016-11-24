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
    return tmp;
}

rbtreeNode* rbt_rotateLeft(rbtreeNode* center){
    qLog("CALL ROTATEL");
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
    qLog("CALL ROTATER");
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
    qLog("CALL PUT_PRIV");
    (*root)=rbt_put_priv((*root),key,value,(*root)->keyStep,(*root)->valStep,cmp);
    (*root)->color=Q_RBTREE_BLACK;
}

rbtreeNode* rbt_put_priv(rbtreeNode* node,void* key,void* value,int keyStep,int valueStep,int (*cmp)(void*,void*)){
    if(node==NULL){
        qLog("NODE NULL TRIGGERED.");
        rbtreeNode* tmp=rbt_constructor(keyStep,valueStep);
        tmp->color=Q_RBTREE_RED;
        tmp->key=malloc(keyStep);
        memcpy(tmp->key,key,keyStep);
        tmp->value=malloc(valueStep);
        memcpy(tmp->value,value,valueStep);
        qLog("NODE NULL RETURNED.");
        return tmp;
    }
    int cmpresult=cmp(key,node->key);
    if(cmpresult<0)
        node->lchild=rbt_put_priv(node->lchild,key,value,keyStep,valueStep,cmp);
    else if(cmpresult>0)
        node->rchild=rbt_put_priv(node->rchild,key,value,keyStep,valueStep,cmp);
    else
        memcpy(node->value,value,valueStep);
    qLog("REBALANCE TRIGGERED.");
    rbtreeNode* tmp=node;
    if((tmp->rchild!=NULL) && (tmp->lchild!=NULL) && rbt_isRed(tmp->rchild) && !rbt_isRed(tmp->lchild)) tmp=rbt_rotateLeft(tmp);
    if((tmp->lchild!=NULL) && (tmp->lchild->lchild!=NULL) &&rbt_isRed(tmp->lchild) && rbt_isRed(tmp->lchild->lchild)) tmp=rbt_rotateRight(tmp);
    if((tmp->rchild!=NULL) && (tmp->lchild!=NULL) &&rbt_isRed(tmp->lchild) && rbt_isRed(tmp->rchild)) rbt_flipColors(tmp);
    qLog("REBALANCE FINISHED");
    tmp->counts=rbt_size(tmp->lchild)+rbt_size(tmp->rchild)+1;
    return tmp;
}

void rbt_remove(rbtreeNode** root,void* key,int (*cmp)(void*,void*)){
    if(((*root)->lchild)!=NULL && ((*root)->rchild)!=NULL && !rbt_isRed((*root)->lchild) && !rbt_isRed((*root)->rchild))
        (*root)->color=Q_RBTREE_RED;
    qLog("CALL REMOVE_PRIV");
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
    qLog("CALL MOVEREDLEFT");
    rbtreeNode* tmp=parent;
    rbt_reverseFlipColors(parent);
    if(tmp->rchild!=NULL && tmp->rchild->lchild!=NULL && rbt_isRed(parent->rchild->lchild)){
        parent->rchild=rbt_rotateRight(parent->rchild);
        tmp=rbt_rotateLeft(tmp);
    }
    return tmp;
}

rbtreeNode* rbt_moveRedRight(rbtreeNode* parent){
    qLog("CALL MOVEREDRIGHT");
    rbtreeNode* tmp=parent;
    rbt_reverseFlipColors(tmp);
    if(tmp->lchild!=NULL && tmp->lchild->lchild!=NULL && !rbt_isRed(tmp->lchild->lchild))
        tmp=rbt_rotateRight(tmp);
    return tmp;
}

rbtreeNode* rbt_getMin(rbtreeNode* node){
    if(node->lchild==NULL)
        return node;
    return node->lchild;
}

void* rbt_getValue(rbtreeNode* node,void* key,int (*cmp)(void*,void*)){
    if(node==NULL){
        qLog("SEARCH REACHED EMPTY NODE.");
        return NULL;
    }
    printf("comparing %d with %d\n",*((int*)key),*((int*)node->key));
    int cmpresult=cmp(key,node->key);
    if(cmpresult<0)
        return rbt_getValue(node->lchild,key,cmp);
    else if(cmpresult>0)
        return rbt_getValue(node->rchild,key,cmp);
    else
        return node->value;
}

rbtreeNode* rbt_balance(rbtreeNode* node){
    qLog("HIT REBALANCING");
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
        qLog("HIT LESSER");
        if(tmp->lchild!=NULL && tmp->lchild->lchild!=NULL && !rbt_isRed(tmp->lchild) && !rbt_isRed(tmp->lchild->lchild))
            tmp=rbt_moveRedLeft(tmp);
        rbtreeNode* tmptr=rbt_remove_priv(tmp->lchild,key,keyStep,cmp);
        if(tmp!=NULL && tmptr==NULL){
            qLog("HIT DELETED");
            free(tmp->lchild->key);
            free(tmp->lchild->value);
            free(tmp->lchild);
        }
        qLog("FREE FINISHED.");
        tmp->lchild=tmptr;
    }else{
        qLog("HIT NOTLESSER");
        if(tmp->lchild!=NULL && rbt_isRed(tmp->lchild))
            tmp=rbt_rotateRight(tmp);
        qLog("CMP key,tmpkey");
        if(cmp(key,tmp->key)==0 && (tmp->rchild == NULL))
            return NULL;
        if(tmp->rchild!=NULL && tmp->rchild->lchild!=NULL && !rbt_isRed(tmp->rchild) && !rbt_isRed(tmp->rchild->lchild))
            tmp=rbt_moveRedRight(tmp);
        if(cmp(key,tmp->key)==0){
            qLog("HIT EQUAL");
            memcpy(tmp->value,rbt_getValue(tmp->rchild,(rbt_getMin(tmp->rchild))->key,cmp),tmp->valStep);
            memcpy(tmp->key,rbt_getMin(tmp->rchild)->key,keyStep);
            rbtreeNode* tmptr=rbt_removeMin(tmp->rchild);
            if(tmp!=NULL && tmptr==NULL){
                free(tmp->rchild->key);
                free(tmp->lchild->value);
                free(tmp->lchild);
            }
            tmp->rchild=tmptr;
        }else{
            qLog("HIT NOEQUAL");
            if(tmp->rchild==NULL)
                return NULL;
            rbtreeNode* tmptr=rbt_remove_priv(tmp->rchild,key,keyStep,cmp);
            qLog("RBT_REMOVE RETURNED NULL.");
            if(tmp!=NULL && tmptr==NULL){
                qLog("HIT DELETED");
                free(tmp->rchild->key);
                free(tmp->rchild->value);
                free(tmp->rchild);
            }
            tmp->rchild=tmptr;
        }
    }
    return rbt_balance(tmp);
}
