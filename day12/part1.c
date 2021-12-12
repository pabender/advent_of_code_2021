#include "common.h"

typedef struct node{
    char *label;
    int index;
} cave;

int adjacency[100][100];
int paths[100][100];

int numCaves=0;
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
    numCaves++;
    return caves[numCaves-1];
}

int initAdjacency(list input){
    char node1[100];
    char node2[100];
    for(int i=0;i<input.size;i++){
        sscanf(input.data[i]," %[^-]-%s",&node1,&node2);
        cave cave1=getCave(node1);
        cave cave2=getCave(node2);
        adjacency[cave1.index][cave2.index]=1;
        paths[cave1.index][cave2.index]=1;
        if(strcmp(toupper(cave1.label),cave1.label)== 0 ||
                strcmp(toupper(cave2.label),cave2.label)==0) {
           adjacency[cave2.index][cave1.index]=1;
           paths[cave2.index][cave1.index]=1;
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

   return(paths[cave1.index][cave2.index]);

}

int findEntry(int row,int column){
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

   for(int i=0;i<4;i++){
       multiplyAdjacency();
   }
   printAdjacency();
   //printPaths();


   printf("paths from start to end: %i\n",numPaths());

   return 0;
}
