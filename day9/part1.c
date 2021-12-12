#include "common.h"


int **convertInputToArrayOfInt(list input){
  int **output = malloc(sizeof(int *)*input.size);
  for(int i=0;i<input.size;i++){
      output[i]=malloc(sizeof(int)*strlen(input.data[i]));
      for(int j=0;j<strlen(input.data[i]);j++){
          //output[i][j]=atoi(input.data[i][j]);
          output[i][j]=(input.data[i][j])-'0';
          printf("%i ",output[i][j]);
      }
      printf("\n");
  }
  return output;
}
int findFirstRowLowPointRisk(int **map,int columns){
   int risk = 0;
   int i = 0;
   for(int j = 0; j<columns;j++){
       if(j==0){
          // first column
          if(map[i][j]<map[i+1][j] && map[i][j]<map[i][j+1]){
             risk += map[i][j] + 1;
                printf("a lowpoint (%i,%i) = %i\n",i,j,map[i][j]);
          }
            } else if(j==columns-1) {
                // last column
          if(map[i][j]<map[i+1][j] && map[i][j]<map[i][j-1]){
             risk += map[i][j] + 1;
                printf("b lowpoint (%i,%i) = %i\n",i,j,map[i][j]);
          }
            } else {
                // all other entries
                if(map[i][j]<map[i+1][j] &&
                  map[i][j]<map[i][j-1] &&
                  map[i][j]<map[i][j+1]){
                  risk += map[i][j] + 1;
                printf("c lowpoint (%i,%i) = %i\n",i,j,map[i][j]);
               }
            }
   }
   return risk;
}

int findLastRowLowPointRisk(int **map,int columns,int rows){
   int risk = 0;
   int i = rows-1;
   for(int j = 0; j<columns;j++){
            if(j==0){
                if(map[i][j] < map[i-1][j] &&
                    map[i][j]<map[i][j+1]){
                   risk += map[i][j] + 1;
                printf("d lowpoint (%i,%i) = %i\n",i,j,map[i][j]);
                }
            } else if(j==columns-1){
                printf("b\n");
             if(map[i][j] < map[i-1][j] &&
                  map[i][j]<map[i][j-1]){
                risk += map[i][j] + 1;
                printf("e lowpoint (%i,%i) = %i\n",i,j,map[i][j]);
             }
            } else {
                printf("c\n");
             if(map[i][j] < map[i-1][j] &&
                  map[i][j]<map[i][j-1] &&
                  map[i][j]<map[i][j+1]){
                risk += map[i][j] + 1;
                printf("f lowpoint (%i,%i) = %i\n",i,j,map[i][j]);
             }
            }
   }
   return risk;
}

int findMiddleRowLowPointRisk(int **map,int columns,int row){
   int risk = 0;
   int i = row;
   for(int j = 0; j<columns;j++){
            if(j==0){
             if(map[i][j] < map[i-1][j] &&
                map[i][j] < map[i+1][j] &&
                  map[i][j]<map[i][j+1]){
                risk += map[i][j] + 1;
                printf("g lowpoint (%i,%i) = %i\n",i,j,map[i][j]);
             }
            } else if(j==columns-1){
             if(map[i][j] < map[i-1][j] &&
                map[i][j] < map[i+1][j] &&
                  map[i][j]<map[i][j-1]){
                risk += map[i][j] + 1;
                printf("h lowpoint (%i,%i) = %i\n",i,j,map[i][j]);
             }
            } else {
             if(map[i][j]<map[i-1][j] &&
                  map[i][j]<map[i+1][j] &&
                  map[i][j]<map[i][j-1] &&
                  map[i][j]<map[i][j+1]){
                risk += map[i][j] + 1;
                printf("i lowpoint (%i,%i) = %i\n",i,j,map[i][j]);
             }
            }
   }
   return risk;
}


int findLowPointRisk(int **map,int columns,int rows){
   int risk = 0;

   for(int i = 0; i<rows;i++){
       if(i == 0){
            // first row
            risk += findFirstRowLowPointRisk(map,columns);
       } else if(i==rows-1){
              // last row
            risk += findLastRowLowPointRisk(map,columns,rows);
          } else {
              // general case;
            risk += findMiddleRowLowPointRisk(map,columns,i);
          }
       //printf("%i risk %i\n",i,risk);
     }
    return risk;
}

int main(int argc,char **argv){

   list *input = stringList(argv[1]);
   printList(input);
   int linelength= strlen(input->data[0]);
   printf("before convert\n");
   int **map = convertInputToArrayOfInt(*input);
   printf("after convert\n");
   int risk = findLowPointRisk(map,linelength,input->size);
   printf("low point risk %i\n",risk);

   return 0;
}
