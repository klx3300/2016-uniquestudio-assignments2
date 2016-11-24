#include <stdio.h>
#include "rbtree.h"

int cmpints(void* a,void* b){
    int v1=(*((int*)a));
    int v2=(*((int*)b));
    return v1-v2;
}

int main(void){
    rbtreeNode *tree=qRedBlackTree(int,int);
    int a=1,b=2;
    rbt_insert(&tree,&a,&b,cmpints);
    a=2,b=3,rbt_insert(&tree,&a,&b,cmpints);
    a=3,b=4;rbt_insert(&tree,&a,&b,cmpints);
    a=6,b=3,rbt_insert(&tree,&a,&b,cmpints);
    a=5,b=2,rbt_insert(&tree,&a,&b,cmpints);
    a=4;b=1,rbt_insert(&tree,&a,&b,cmpints);
    a=3,b=7,rbt_insert(&tree,&a,&b,cmpints);

    a=6,b=3,rbt_insert(&tree,&a,&b,cmpints);
    a=8,b=4;rbt_insert(&tree,&a,&b,cmpints);
    a=17,b=3,rbt_insert(&tree,&a,&b,cmpints);
    a=12,b=2,rbt_insert(&tree,&a,&b,cmpints);
    a=198;b=1,rbt_insert(&tree,&a,&b,cmpints);
    a=123,b=7,rbt_insert(&tree,&a,&b,cmpints);
    
    a=4444,b=3,rbt_insert(&tree,&a,&b,cmpints);
    a=2333,b=4;rbt_insert(&tree,&a,&b,cmpints);
    a=1222,b=3,rbt_insert(&tree,&a,&b,cmpints);
    a=56789,b=2,rbt_insert(&tree,&a,&b,cmpints);
    a=12344;b=1,rbt_insert(&tree,&a,&b,cmpints);
    a=198,b=998,rbt_insert(&tree,&a,&b,cmpints);
    
    a=123;rbt_remove(&tree,&a,cmpints);
    printf("REMOVE FIRST COMPLETED.\n");
    a=17;rbt_remove(&tree,&a,cmpints);
    a=4;rbt_remove(&tree,&a,cmpints);
    a=12344;rbt_remove(&tree,&a,cmpints);
    printf("TRYING TO DELETE NON-EXIST ELEMENT.\n");
    a=9988;rbt_remove(&tree,&a,cmpints);
    printf("NOT THIS PROBLEM\n");
    return 0;
}
