#include<stdio.h>
#include<stdlib.h>
#include"voidutils.h"
void nextStep(void** rptr,int stepLength){
    (*rptr)+=stepLength;
}

void fakeSegmentFault(const char* errmsg){
    printf("Runtime Error:%s\n",errmsg);
    printf("Segmentation Fault.(Core Dumped)\n");
    exit(0);
}

void fakeSegmentNotFault(const char* errmsg){
    printf("Runtime Error:%s\n",errmsg);
}

void qLog(const char* errmsg){
    printf("LOG\t%s\n",errmsg);
}

void rreach(void** rptr,int index,int stepLength){
    (*rptr)+=(stepLength*index);
}
void* sreach(void* ptr,int index,int stepLength){
    void* tmptr=ptr;
    rreach(&tmptr,index,stepLength);
    return tmptr;
}
