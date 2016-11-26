#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// your headers*********************
#include "set.h"
// custom headers end***************

const unsigned int FLAG_INSERT=1;
const unsigned int FLAG_SEARCH=2;
const unsigned int FLAG_DELETE=4;
const unsigned int FLAG_ITERATION_FRONT=8;
const unsigned int FLAG_ITERATION_BACK=16;

const int RANDOM_SEED_VALUE=198;
const int LEVEL_1_SIZE=32768;
const int LEVEL_2_SIZE=65536;
const int LEVEL_3_SIZE=131072;
const int LEVEL_4_SIZE=524288;
const int LEVEL_5_SIZE=2097152;
const int LEVEL_6_SIZE=16777216;
const int LEVEL_7_SIZE=134217728;

// custom operation details on ************************

// which test would be run.
// sample given below.
unsigned int FLAG_WHICH_TEST= FLAG_INSERT | FLAG_SEARCH | FLAG_DELETE | FLAG_ITERATION_FRONT | FLAG_ITERATION_BACK;

int comparator(void* a,void* b){
    return (*(int*)a)-(*(int*)b);
}

void insert_operation(void* container,int key,int value){
    // convert the void ptr to your container and then start.
    int k=key,v=value;
    set_insert((Set*)container,&k,&v);
}

void* initialize_operation(int maxsize){
    // call your constructor and then return.
    Set* st=qSet(int,int,comparator);
    return st;    
}

void search_operation(void* container,int key){
    int k=key;
    rbt_getValue(((Set*)container)->root,&k,comparator);
}

void erase_operation(void* container,int key){
    int k=key;
    set_erase((Set*)container,&k);
}

void* init_iterator_first(void* container){
    // call your constructor
    
    return set_begin((Set*)container);
}

void* init_iterator_last(void* container){

    return set_end((Set*)container);
}

void iterator_increase(void* iterator){
    // increase your iterator
    SetIterator_self_increase((SetIterator*)iterator);
}

void iterator_decrease(void* iterator){
    // decrease your iterator
    SetIterator_self_decrease((SetIterator*)iterator);
}

int iteration_end_flag(void* iterator){
    // this func will be called to check if iterator meets its end value.
    // if it does meet,return true
    // otherwise,false instead.
    
    return ((SetIterator*)iterator)->ptr->current==NULL;
}

// custom operation details end **********************
void tester(int size){
    void* container=initialize_operation(size);
    int* keyArray=malloc(sizeof(int)*size);
    int* valueArray=malloc(sizeof(int)*size);
    // initialize
    // time calculation start;
    struct timeval start,end;
    if(FLAG_WHICH_TEST & FLAG_INSERT){
        printf("TEST\tINSERTION\n");
        for(int i=0;i<size;i++){
            keyArray[i]=rand();
            valueArray[i]=rand();
        }
        gettimeofday(&start,NULL);
        for(int i=0;i<size;i++){
            insert_operation(container,keyArray[i],valueArray[i]);
        }
        gettimeofday(&end,NULL);
        printf("RESULT\n\ttime consumption:%ld\n",(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec));
    }
    if(FLAG_WHICH_TEST & FLAG_SEARCH){
        printf("TEST\tSEARCH\n");
        for(int i=0;i<size;i++){
            keyArray[i]=rand();
        }
        gettimeofday(&start,NULL);
        for(int i=0;i<size;i++){
            search_operation(container,keyArray[i]);
        }
        gettimeofday(&end,NULL);
        printf("RESULT\n\ttime consumption:%ld\n",(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec));
    }
    if(FLAG_WHICH_TEST & FLAG_ITERATION_FRONT){
        printf("TEST\tITERATION FROM FRONT\n");
        for(int i=0;i<size;i++){
            keyArray[i]=rand();
        }
        gettimeofday(&start,NULL);
        for(void* iter=init_iterator_first(container);!iteration_end_flag(iter);iterator_increase(iter)){
        }
        gettimeofday(&end,NULL);
        printf("RESULT\n\ttime consumption:%ld\n",(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec));
    }
    if(FLAG_WHICH_TEST & FLAG_ITERATION_BACK){
        printf("TEST\tITERATION FROM BACK\n");
        for(int i=0;i<size;i++){
            keyArray[i]=rand();
        }
        gettimeofday(&start,NULL);
        for(void* iter=init_iterator_last(container);!iteration_end_flag(iter);iterator_decrease(iter)){
        }
        gettimeofday(&end,NULL);
        printf("RESULT\n\ttime consumption:%ld\n",(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec));
    }
    if(FLAG_WHICH_TEST & FLAG_DELETE){
        printf("TEST\tDELETION\n");
        for(int i=0;i<size;i++){
            keyArray[i]=rand();
        }
        gettimeofday(&start,NULL);
        for(int i=0;i<size;i++){
            erase_operation(container,keyArray[i]);
        }
        gettimeofday(&end,NULL);
        printf("RESULT\n\ttime consumption:%ld\n",(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec));
    }
    printf("TEST WITH SAMPLE SIZE %d OVER.\n",size);
    system("read -p \"PRESS ENTER TO CONTINUE\" var");
    printf("\n");
}

int main(void){
    srand(RANDOM_SEED_VALUE);
    tester(LEVEL_1_SIZE);
    tester(LEVEL_2_SIZE);
    tester(LEVEL_3_SIZE);
    tester(LEVEL_4_SIZE);
    tester(LEVEL_5_SIZE);
    tester(LEVEL_6_SIZE);
    tester(LEVEL_7_SIZE);
    return 0;
}
