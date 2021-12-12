#include "common.h"

void initFishCountArray(char *input,unsigned long fishCountArray[9]){
    char *nextValue = strtok(input,",");
    while(nextValue!=NULL){
        fishCountArray[atoi(nextValue)]++;
        nextValue = strtok(NULL,",");
    }
}

unsigned long simulateDay(unsigned long fishCountArray[9]){
    unsigned long newValueArray[9];
    newValueArray[8]=fishCountArray[0];
    newValueArray[0]=fishCountArray[1];
    newValueArray[1]=fishCountArray[2];
    newValueArray[2]=fishCountArray[3];
    newValueArray[3]=fishCountArray[4];
    newValueArray[4]=fishCountArray[5];
    newValueArray[5]=fishCountArray[6];
    newValueArray[6]=fishCountArray[7]+fishCountArray[0];
    newValueArray[7]=fishCountArray[8];

    unsigned long endingFish = 0;
    for(int i=0;i<9;i++){
        fishCountArray[i]=newValueArray[i];
        endingFish += newValueArray[i];
    }

    return endingFish;
}

int main(int argc,char **argv){

   list *input = stringList(argv[1]);
   //printList(input);

   unsigned long fishCountArray[9]={0,0,0,0,0,0,0,0,0};

   initFishCountArray(input->data[0],fishCountArray);  
   unsigned long initialFishCount = 0;

   for(int i=0;i<256;i++){
      //printf("%i count %i\n",i,initialFishCount);
      initialFishCount = simulateDay(fishCountArray);
   }

   printf("The final fish count is %lu\n",initialFishCount);

   return 0;
}
