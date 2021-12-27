#include "common.h"
#include <string.h>

char **fillGrid(list input)
{
    char **grid=malloc(sizeof(char *)*input.size);
    for(int i=0;i<input.size;i++){
       grid[i]=malloc(sizeof(char)*(strlen(input.data[i])+1));
       int j;
       for(j=0;j<=strlen(input.data[i]);j++){
          grid[i][j]=input.data[i][j];
       }
       grid[i][j]='\0';
    }
    return grid;
}

void printgrid(char **grid,int rows){
  for(int i=0;i<rows;i++){
     printf("%s\n",grid[i]);
  }
}

int gridcompare(char **A,char **B,int rows){
  int lastcompare;
  for(int i=0;i<rows;i++){
     if(lastcompare=strcmp(A[i],B[i])!=0) break;
  }
  return lastcompare;
}

char **moveSouth(char **original,int rows){
   int width=strlen(original[0]);
   char **result=malloc(sizeof(char *)*rows);
   for(int i=0;i<rows;i++){
      result[i]=malloc(sizeof(char)*(width+1));
      strcpy(result[i],original[i]);
   }
   for(int i=0;i<rows;i++) {
      for(int j=0;j<=width;j++){
	if(original[i][j]=='v' && original[(i+1)%rows][j]=='.'){
          //printf("move\n");
	  result[i][j]='.';
	  result[(i+1)%rows][j]=original[i][j];
	}
      }
   }
   return result;
}

char **moveEast(char **original,int rows){
   int width=strlen(original[0]);
   char **result=malloc(sizeof(char *)*rows);
   for(int i=0;i<rows;i++){
      result[i]=malloc(sizeof(char)*(width+1));
      strcpy(result[i],original[i]);
   }
   for(int i=0;i<rows;i++) {
      for(int j=0;j<=width;j++){
	if(original[i][j]=='>' && original[i][(j+1)%width]=='.'){
          //printf("move\n");
	  result[i][j]='.';
	  result[i][(j+1)%width]=original[i][j];
	}
      }
   }
   return result;
}

int main(int argc,char **argv){

   list *input = stringList(argv[1]);
   //printList(input);
   int rows = input->size;
   char **grid = fillGrid(*input);
   //printgrid(grid,rows);

   char **newgrid;
   int steps=0;

   newgrid=grid;

   do{
     steps++;
     grid=newgrid;
     newgrid=moveEast(grid,rows);
     newgrid=moveSouth(newgrid,rows);
     //printgrid(newgrid,rows);
     //break;
   } while(gridcompare(newgrid,grid,rows)!=0);


   printf("stopped after %i steps\n",steps);

   return 0;
}
