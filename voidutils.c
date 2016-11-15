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
