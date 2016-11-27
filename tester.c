#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// your headers*********************

// custom headers end***************

const unsigned int FLAG_INSERT=1;
const unsigned int FLAG_SEARCH=2;
const unsigned int FLAG_DELETE=4;
const unsigned int FLAG_ITERATION_FRONT=8;
const unsigned int FLAG_ITERATION_BACK=16;
const unsigned int FLAG_LESS_COINCIDENCE=32;
const unsigned int FLAG_COMPARING=64;

const int RANDOM_SEED_VALUE=198;
const int LEVEL_1_SIZE=32768;
const int LEVEL_2_SIZE=65536;
const int LEVEL_3_SIZE=131072;
const int LEVEL_4_SIZE=524288;
const int LEVEL_5_SIZE=2097152;
const int LEVEL_6_SIZE=16777216;
const int LEVEL_7_SIZE=134217728;

int RESULT_OF_INSERTION[5];
int RESULT_OF_SEARCHING[5];
int RESULT_OF_DELETION[5];
int RESULT_OF_ITERATION_FRONT[5];
int RESULT_OF_ITERATION_BACK[5];

int RESULT_OF_INSERTION_EACHLVL[7];
int RESULT_OF_SEARCHING_EACHLVL[7];
int RESULT_OF_DELETION_EACHLVL[7];
int RESULT_OF_ITERATION_FRONT_EACHLVL[7];
int RESULT_OF_ITERATION_BACK_EACHLVL[7];

// custom operation details on ************************

// which test would be run.
// sample given below.
const unsigned int FLAG_WHICH_TEST= FLAG_INSERT | FLAG_SEARCH | FLAG_DELETE;


// how many levles runned before the results come out.
const unsigned int HOW_MANY_LEVELS_TO_TEST = 7;

void insert_operation(void* container,int key,int value){
    // convert the void ptr to your container and then start.

}

void* initialize_operation(int maxsize){
    // call your constructor and then return.

    return NULL;    
}

void search_operation(void* container,int key){

}

void erase_operation(void* container,int key){

}

void* init_iterator_first(void* container){
    // call your constructor
    
    return NULL;
}

void* init_iterator_last(void* container){

    return NULL;
}

void iterator_increase(void* iterator){
    // increase your iterator

}

void iterator_decrease(void* iterator){
    // decrease your iterator

}

int iteration_end_flag(void* iterator){
    // this func will be called to check if iterator meets its end value.
    // if it does meet,return true
    // otherwise,false instead.
    
    return 1;
}

void free_container(void* container){
    // free the memory allocated by the container_init
    
}

void free_iterator(void* iterator){
    // free the memory allocated by the iterator_init
}

// custom operation details end **********************

int getAverage(int* arrayhead,int counts){
    int avg=0;
    for(int i=0;i<counts;i++){
        avg+=arrayhead[i];
    }
    return avg/counts;
}

int CURRENT_TEST_REPEAT_COUNT=0;
int CURRENT_LEVEL=0;
void tester(int size){
    if(CURRENT_LEVEL>=HOW_MANY_LEVELS_TO_TEST)
        return;
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
        RESULT_OF_INSERTION[CURRENT_TEST_REPEAT_COUNT]=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
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
        RESULT_OF_SEARCHING[CURRENT_TEST_REPEAT_COUNT]=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
        printf("RESULT\n\ttime consumption:%ld\n",(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec));
    }
    if(FLAG_WHICH_TEST & FLAG_ITERATION_FRONT){
        printf("TEST\tITERATION FROM FRONT\n");
        for(int i=0;i<size;i++){
            keyArray[i]=rand();
        }
        void* iter=init_iterator_first(container);
        gettimeofday(&start,NULL);
        for(;!iteration_end_flag(iter);iterator_increase(iter)){
        }
        gettimeofday(&end,NULL);
        free_iterator(iter);
        RESULT_OF_ITERATION_FRONT[CURRENT_TEST_REPEAT_COUNT]=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
        printf("RESULT\n\ttime consumption:%ld\n",(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec));
    }
    if(FLAG_WHICH_TEST & FLAG_ITERATION_BACK){
        printf("TEST\tITERATION FROM BACK\n");
        for(int i=0;i<size;i++){
            keyArray[i]=rand();
        }
        void* iter=init_iterator_last(container);
        gettimeofday(&start,NULL);
        for(;!iteration_end_flag(iter);iterator_decrease(iter)){
        }
        gettimeofday(&end,NULL);
        free_iterator(iter);
        RESULT_OF_ITERATION_BACK[CURRENT_TEST_REPEAT_COUNT]=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
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
    free_container(container);
    if(FLAG_WHICH_TEST & FLAG_LESS_COINCIDENCE)
        ;
    else
        system("read -p \"PRESS ENTER TO CONTINUE\" var");
    printf("\n");
}

void getStastistics(void){

    if(FLAG_WHICH_TEST & FLAG_INSERT){
        RESULT_OF_INSERTION_EACHLVL[CURRENT_LEVEL]=getAverage(RESULT_OF_INSERTION,5);
    }
    if(FLAG_WHICH_TEST & FLAG_SEARCH){
        RESULT_OF_SEARCHING_EACHLVL[CURRENT_LEVEL]=getAverage(RESULT_OF_SEARCHING,5);
    }
    if(FLAG_WHICH_TEST & FLAG_DELETE){
        RESULT_OF_DELETION_EACHLVL[CURRENT_LEVEL]=getAverage(RESULT_OF_DELETION,5);
    }
    if(FLAG_WHICH_TEST & FLAG_ITERATION_FRONT){
        RESULT_OF_ITERATION_FRONT_EACHLVL[CURRENT_LEVEL]=getAverage(RESULT_OF_ITERATION_FRONT,5);
    }
    if(FLAG_WHICH_TEST & FLAG_ITERATION_BACK){
        RESULT_OF_ITERATION_BACK_EACHLVL[CURRENT_LEVEL]=getAverage(RESULT_OF_ITERATION_BACK,5);
    }
}/*
void calcDivergence(int* array){
    if(HOW_MANY_LEVELS_TO_TEST<3){
        printf("TOO LESS LEVELS TO COME TO AN CONCLUSION.\nSTOP.\n");
        return;
    }
    double divergence=0;
    divergence+=((double)array[1])/((double)array[0]);
    divergence+=((double)array[2])/((double)array[1]);
    divergence=divergence/2;
    if(HOW_MANY_LEVELS_TO_TEST<5){
        if(divergence-1.0<0.1){
            printf("Complexity:\n O(1) or O(logN)\n");
        }else if(divergence-2.0<0.1){
            printf("Complexity:\n O(n)\n");
        }else if(divergence-2.12<0.01){
            printf("Complexity:\n O(NlogN)\n");
        }else{
            printf("Complexity:\nlarger than O(NlogN)");
        }
    }
}*/

void printStastistics(int* array){
    for(int i=0;i<HOW_MANY_LEVELS_TO_TEST;i++){
        printf("%d ",array[i]);
    }
    printf("\n");
}

int main(void){
    srand(RANDOM_SEED_VALUE);
    do{
        tester(LEVEL_1_SIZE);
        CURRENT_TEST_REPEAT_COUNT++;
    }while(CURRENT_TEST_REPEAT_COUNT<5 && (FLAG_WHICH_TEST & FLAG_LESS_COINCIDENCE));
    getStastistics();
    CURRENT_TEST_REPEAT_COUNT=0;CURRENT_LEVEL++;
    do{
        tester(LEVEL_2_SIZE);
        CURRENT_TEST_REPEAT_COUNT++;
    }while(CURRENT_TEST_REPEAT_COUNT<5 && (FLAG_WHICH_TEST & FLAG_LESS_COINCIDENCE));
    getStastistics();
    CURRENT_TEST_REPEAT_COUNT=0;CURRENT_LEVEL++;
    do{
        tester(LEVEL_3_SIZE);
        CURRENT_TEST_REPEAT_COUNT++;
    }while(CURRENT_TEST_REPEAT_COUNT<5 && (FLAG_WHICH_TEST & FLAG_LESS_COINCIDENCE));
    getStastistics();
    CURRENT_TEST_REPEAT_COUNT=0;CURRENT_LEVEL++;
    do{
        tester(LEVEL_4_SIZE);
        CURRENT_TEST_REPEAT_COUNT++;
    }while(CURRENT_TEST_REPEAT_COUNT<5 && (FLAG_WHICH_TEST & FLAG_LESS_COINCIDENCE));
    getStastistics();
    CURRENT_TEST_REPEAT_COUNT=0;CURRENT_LEVEL++;
    do{
        tester(LEVEL_5_SIZE);
        CURRENT_TEST_REPEAT_COUNT++;
    }while(CURRENT_TEST_REPEAT_COUNT<5 && (FLAG_WHICH_TEST & FLAG_LESS_COINCIDENCE));
    getStastistics();
    CURRENT_TEST_REPEAT_COUNT=0;CURRENT_LEVEL++;
    do{
        tester(LEVEL_6_SIZE);
        CURRENT_TEST_REPEAT_COUNT++;
    }while(CURRENT_TEST_REPEAT_COUNT<5 && (FLAG_WHICH_TEST & FLAG_LESS_COINCIDENCE));
    getStastistics();
    CURRENT_TEST_REPEAT_COUNT=0;CURRENT_LEVEL++;
    do{
        tester(LEVEL_7_SIZE);
        CURRENT_TEST_REPEAT_COUNT++;
    }while(CURRENT_TEST_REPEAT_COUNT<5 && (FLAG_WHICH_TEST & FLAG_LESS_COINCIDENCE));
    getStastistics();
    CURRENT_TEST_REPEAT_COUNT=0;CURRENT_LEVEL++;
    printf("******************************\nTEST REPORT:\n");
    printf("TOTAL LEVLES RUNNED:%d\n",HOW_MANY_LEVELS_TO_TEST);
    if(FLAG_WHICH_TEST & FLAG_INSERT){printf("INSERTION RESULTS: ");printStastistics(RESULT_OF_INSERTION_EACHLVL);}
    if(FLAG_WHICH_TEST & FLAG_SEARCH){printf("SEARCHING RESULTS: ");printStastistics(RESULT_OF_SEARCHING_EACHLVL);}
    if(FLAG_WHICH_TEST & FLAG_DELETE){printf("REMOVMENT RESULTS: ");printStastistics(RESULT_OF_DELETION_EACHLVL); }
    if(FLAG_WHICH_TEST & FLAG_ITERATION_FRONT){printf("ITERATION FRONT RESULTS: ");printStastistics(RESULT_OF_ITERATION_FRONT_EACHLVL);}
    if(FLAG_WHICH_TEST & FLAG_ITERATION_BACK){printf("ITERATION BACK RESULTS: ");printStastistics(RESULT_OF_ITERATION_BACK_EACHLVL);}
    printf("REPORT END.\n*********************************\n");
    return 0;
}
