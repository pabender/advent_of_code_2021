#include <stdio.h>
#include <stdlib.h>
#include "intmethods.h"

int nextValue(int *array,int startPos){
    return array[startPos]+array[startPos-1]+array[startPos-2];
}

int main(int argc,char **argv){

    int *observations = getIntArray(argv[1]);
    printf("increases %i\n",countChangesInArray(observations,&nextValue,2));

   return 0;

}
