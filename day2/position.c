#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "positionMethods.h"

int main(int argc, char **argv){

    FILE *f = fopen(argv[1],"r");
    char command[20];
    int move;
        
    fscanf(f,"%s %d",&command, &move);

    do {
        //printf("%s %d\n",command,move);
        if(strcmp("forward",command)==0){
            forward(move);
        } else if(strcmp("up",command)==0){
            up(move);
        } else if(strcmp("down",command)==0){
            down(move);
        }
        fscanf(f,"%s %d",&command, &move);
    } while(!feof(f));

    fclose(f);

    printf( "horizontal position %i, depth %i, product %i\n",
            getCurrentHorizontalPosition(),
            getCurrentDepth(),
            getCurrentHorizontalPosition()*getCurrentDepth()); 

    return 0;
}
