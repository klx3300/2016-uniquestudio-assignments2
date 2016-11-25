#define Q_RBTREE_H
#include <stdbool.h>
#ifndef Q_STACK_H
#include "stack.h"
#endif
#define Q_RBTREE_RED 1
#define Q_RBTREE_BLACK 0
#define Q_RBTREE_IDENTITY_LEFT -1
#define Q_RBTREE_IDENTITY_CENTER 0
#define Q_RBTREE_IDENTITY_RIGHT 1
#define qRedBlackTree(Key,Value) rbt_constructor(sizeof(Key),sizeof(Value));
typedef struct rbtreeNode{
    int color;
    struct rbtreeNode* parent;
    struct rbtreeNode* lchild;
    struct rbtreeNode* rchild;
    void* key;
    void* value;
    int counts;
    int keyStep;
    int valStep;
}rbtreeNode;

typedef struct rbtreeIterator{
    struct rbtreeNode* current;
    Stack* status;
}rbtreeIterator;

rbtreeNode* rbt_constructor(int keyStep,int valueStep);
rbtreeNode* rbt_getMin(rbtreeNode* node);
void* rbt_getValue(rbtreeNode* node,void* key,int (*cmp)(void*,void*));
rbtreeNode* rbt_rotateLeft(rbtreeNode* center);
rbtreeNode* rbt_rotateRight(rbtreeNode* center);
void rbt_flipColors(rbtreeNode* parent);
void rbt_reverseFlipColors(rbtreeNode* parent);
rbtreeNode* rbt_moveRedLeft(rbtreeNode* parent);
rbtreeNode* rbt_moveRedRight(rbtreeNode* parent);
rbtreeNode* rbt_balance(rbtreeNode* node);
bool rbt_isRed(rbtreeNode* node);
int rbt_size(rbtreeNode* node);
rbtreeNode* rbt_put_priv(rbtreeNode* node,void* key,void* value,int keyStep,int valueStep,int (*cmp)(void*,void*));
// compare function requirements:
// first>second return >0
// first<second return <0
// first=second return =0
void rbt_insert(rbtreeNode** root,void* key,void* value,int (*cmp)(void*,void*));
rbtreeNode* rbt_removeMin(rbtreeNode* node);
void rbt_remove(rbtreeNode** root,void* key,int (*cmp)(void*,void*));
rbtreeNode* rbt_remove_priv(rbtreeNode* node,void* key,int keyStep,int (*cmp)(void*,void*));

rbtreeIterator* rbtreeIterator_constructor(rbtreeNode* root);
void rbtreeIterator_increase(rbtreeIterator* x);
void rbtreeIterator_decrease(rbtreeIterator* x);
rbtreeIterator* rbt_first(rbtreeNode* root);
rbtreeIterator* rbt_last(rbtreeNode* root);
