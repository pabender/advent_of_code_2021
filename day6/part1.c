#include "common.h"

int fishCountValue;

int *initFishArray(char *input){
    int *fishArray = malloc(sizeof(int)*10000000);
    int currentFish=0;
    char *nextValue = strtok(input,",");
    while(nextValue!=NULL){
        fishArray[currentFish++]=atoi(nextValue);
        nextValue = strtok(NULL,",");
    }
    printf("array count %i\n",currentFish);
    fishCountValue = currentFish;
    return fishArray;
}

int fishCount(char *input){
/*    int currentFish=0;
    char *nextValue = strtok(input,",");
    while(nextValue!=NULL){
        currentFish++; 
        nextValue = strtok(NULL,",");
    }
    printf("count %i\n",currentFish);
    return currentFish;*/
    return fishCountValue;
}

int simulateDay(int *fishArray,int startingFish){
    int endingFish = startingFish;
    for(int fish = 0;fish<startingFish;fish++){
        if(fishArray[fish]==0){
            fishArray[fish]=6;
            fishArray[endingFish++]=8;
        } else {
            fishArray[fish]--;
        }
    }
    return endingFish;
}

int main(int argc,char **argv){

   list *input = stringList(argv[1]);
   //printList(input);
   
   int *fishArray = initFishArray(input->data[0]);  
   int initialFishCount = fishCount(input->data[0]);

   for(int i=0;i<80;i++){
      initialFishCount = simulateDay(fishArray,initialFishCount);
   }

   printf("The final fish count is %i\n",initialFishCount);

   return 0;
}
