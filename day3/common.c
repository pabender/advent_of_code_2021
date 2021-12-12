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
