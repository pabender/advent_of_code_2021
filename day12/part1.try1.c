#include "common.h"
#include <ctype.h>

typedef struct node{
    char *label;
    int index;
    int isSmall;
} cave;

int adjacency[100][100];
int paths[100][100];

typedef struct __pathNode {
	cave *node;
	struct __pathNode* start;
	struct __pathNOde* end;
} path;

path pathList[100];
int totalPaths=0;
int endPaths;

int numCaves=0;
int numBig=0;
int numSmall=0;
int bigEdge=0;
int smallEdge=0;
cave caves[100];

cave getCave(char *label){
    for(int i=0;i<numCaves;i++){
        if(strcmp(caves[i].label,label)==0){
            //printf("existing cave %s\n",label);
            return caves[i];
        }
    }
    //printf("new cave %s\n",label);
    caves[numCaves].label=malloc(sizeof(char)*(strlen(label)+1));
    strcpy(caves[numCaves].label,label);
    caves[numCaves].index=numCaves;
    if(islower(label[0])) {
	    caves[numCaves].isSmall=0;
	    numSmall++;
    } else {
	    caves[numCaves].isSmall=1;
	    numBig++;
    }
    numCaves++;
    return caves[numCaves-1];
}

int initAdjacency(list input){
    char node1[100];
    char node2[100];
    for(int i=0;i<input.size;i++){
        sscanf(input.data[i]," %[^-]-%s",node1,node2);
        cave cave1=getCave(node1);
        cave cave2=getCave(node2);
        adjacency[cave1.index][cave2.index]=1;
        paths[cave1.index][cave2.index]=1;
        if(cave1.isSmall== 1 || cave2.isSmall==1 ) {
           adjacency[cave2.index][cave1.index]=1;
           paths[cave2.index][cave1.index]=1;
	   bigEdge++;
        } else {
           smallEdge++;
	}
    }
}

int initPaths(list input){
    char node1[100];
    char node2[100];
    for(int i=0;i<input.size;i++){
        sscanf(input.data[i]," %[^-]-%s",node1,node2);
        cave cave1=getCave(node1);
        cave cave2=getCave(node2);
        paths[cave1.index][cave2.index]=1;
        if(cave1.isSmall== 1 || cave2.isSmall==1 ) {
           paths[cave2.index][cave1.index]=1;
	   bigEdge++;
        } else {
           smallEdge++;
	}
    }
}

void printAdjacency(){
    for(int i=0;i<numCaves;i++){
        for(int j=0;j<numCaves;j++){
            printf("%i ",adjacency[i][j]);
        }
        printf("\n");
    }
}

void printPaths(){
    for(int i=0;i<numCaves;i++){
        for(int j=0;j<numCaves;j++){
            printf("%i ",paths[i][j]);
        }
        printf("\n");
    }
}

int numPaths(){
   cave cave1=getCave("start");
   cave cave2=getCave("end");

   int startend = paths[cave1.index][cave2.index];
   int endstart = paths[cave2.index][cave1.index];
   printf("paths from start to end: %i\n",paths[cave1.index][cave2.index]);
   printf("paths from end to start: %i\n",paths[cave2.index][cave1.index]);


   return(startend-endstart);

}

int findEntry(int row,int column) {
    int value=0;
    for(int i=0;i<numCaves;i++){
       value +=(paths[row][i]*adjacency[i][column]);
    }
    return value;
}

void multiplyAdjacency(){
    int temp[100][100];
    for(int i=0;i<numCaves;i++){
        for(int j=0;j<numCaves;j++){
            temp[i][j] = findEntry(i,j);
        }
    }
    for(int i=0;i<numCaves;i++){
        for(int j=0;j<numCaves;j++){
            paths[i][j]=temp[i][j];
        }
    }
}


int main(int argc,char **argv){

   list *input = stringList(argv[1]);
   //printList(input);
   initAdjacency(*input);
   //printAdjacency();

   int totalPaths =0;

   int i=0;
       printPaths();
       printf("paths of length %i from start to end: %i\n",i,numPaths());
       totalPaths +=numPaths();
       printf("paths of length %i or less from start to end: %i\n",i,totalPaths);



   int maxlength = bigEdge;

   for(i=0;i<maxlength;i++){
       multiplyAdjacency();
       printPaths();
       printf("paths of length %i from start to end: %i\n",i+1,numPaths());
       totalPaths +=numPaths();
       printf("paths of length %i or less from start to end: %i\n",i+1,totalPaths);
   }
   //printAdjacency();
   printPaths();

   printf("num caves %i big %i small %i small edge %i big edge %i\n",numCaves,numBig,numSmall,smallEdge,bigEdge);

   return 0;
}
