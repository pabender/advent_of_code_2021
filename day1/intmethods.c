#include <stdio.h>
#include <stdlib.h>

#define DATASIZE 10000

int *getIntArray(char *filename){

    int *retval = malloc(sizeof(int) * DATASIZE);
    int count=0;

    FILE *f = fopen(filename,"r");

    for(int i=0;i<DATASIZE;i++){
        retval[i]=-1;
    }

    while(!feof(f)){
        fscanf(f,"%d",retval+count);
        count++;
    }

    fclose(f);
    return retval;
}

int countChangesInArray(int *array,int (*f)(int *,int),int startPos){
    int increases = 0;
    int decreases = 0;
    int last = -1;
    for(int i=startPos;i<DATASIZE;i++){
        if(array[i] == -1){
            break;
        }
        int next = (*f)(array,i);

        if(last == -1){
        }
        else if(last >= next) {
          decreases++;
        } else {
          increases++;
        }
        last = next;
    }
    return increases;
}
