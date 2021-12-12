#include "common.h"
#include <limits.h>

int minValue(int *initialPositions,int numCrabs){
   int minimum = DATASIZE;
   for(int i=0;i<numCrabs;i++){
      if(initialPositions[i]<minimum) {
          minimum=initialPositions[i];
      }
   }
   return minimum;
}

int maxValue(int *initialPositions,int numCrabs){
   int maximum = -1;
   for(int i=0;i<numCrabs;i++){
      if(initialPositions[i]> maximum) {
          maximum=initialPositions[i];
      }
   }
   return maximum;
}

int findMinCost(int *initialPositions,int numCrabs,int minvalue, int maxvalue){
    int minCost = INT_MAX;
    for(int position=minvalue;position<=maxvalue;position++){
        int cost =0;
        for(int i=0;i<numCrabs;i++){
            int currentcost = (abs(initialPositions[i]-position));
            for(int j=1;j<=currentcost;j++){
                cost += j;
            }
        }
        if(cost<minCost) minCost=cost;
        //printf("postion %i cost %i\n",position,cost);
    }
    return minCost;
}

int main(int argc,char **argv){

   list *input = stringList(argv[1]);
   //printList(input);

   int *initialPositions = stringToIntArray(input->data[0]);
   int numCrabs = getArraySize();
   int minPosition = minValue(initialPositions,numCrabs);
   int maxPosition = maxValue(initialPositions,numCrabs);
   printf("minimum cost %i\n",findMinCost(initialPositions,numCrabs,minPosition,maxPosition));

   return 0;
}
