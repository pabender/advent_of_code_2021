#include "common.h"

int maxValues[3]={0,0,0};

void setMaxScore(int i){
    if(i>maxValues[0]){
        maxValues[2]=maxValues[1];
        maxValues[1]=maxValues[0];
        maxValues[0]=i;
    } else if(i>maxValues[1]){
        maxValues[2]=maxValues[1];
        maxValues[1]=i;
    } else if(i>maxValues[2]){
        maxValues[2]=i;
    }
}

int **convertInputToArrayOfInt(list input){
  int **output = malloc(sizeof(int *)*input.size);
  for(int i=0;i<input.size;i++){
      output[i]=malloc(sizeof(int)*strlen(input.data[i]));
      for(int j=0;j<strlen(input.data[i]);j++){
          //output[i][j]=atoi(input.data[i][j]);
          output[i][j]=(input.data[i][j])-'0';
          //printf("%i ",output[i][j]);
      }
      //printf("\n");
  }
  return output;
}

int score(int **map,int rows,int columns,int x,int y){
    //printf("%i %i\n",x,y);
    if(x<0 || y<0 || x>=rows || y>=columns)
        return 0;
    if(map[x][y]==9){
        return 0;
    }
    int value = 0;
    map[x][y]=9;
    value += score(map,rows,columns,x-1,y);
    value += score(map,rows,columns,x+1,y);
    value += score(map,rows,columns,x,y-1);
    value += score(map,rows,columns,x,y+1);
    return 1 + value;
}

int findFirstRowLowPointRisk(int **map,int rows,int columns){
   int risk = 1;
   int i = 0;
   for(int j = 0; j<columns;j++){
       if(j==0){
          // first column
          if(map[i][j]<map[i+1][j] && map[i][j]<map[i][j+1]){
             risk = score(map,rows,columns,i,j);
             setMaxScore(risk);
                printf("a lowpoint (%i,%i) = %i\n",i,j,risk);
          }
            } else if(j==columns-1) {
                // last column
          if(map[i][j]<map[i+1][j] && map[i][j]<map[i][j-1]){
             risk = score(map,rows,columns,i,j);
             setMaxScore(risk);
                printf("b lowpoint (%i,%i) = %i\n",i,j,risk);
          }
            } else {
                // all other entries
                if(map[i][j]<map[i+1][j] &&
                  map[i][j]<map[i][j-1] &&
                  map[i][j]<map[i][j+1]){
                    risk = score(map,rows,columns,i,j);
             setMaxScore(risk);
                printf("c lowpoint (%i,%i) = %i\n",i,j,risk);
               }
            }
   }
   return risk==0?1:risk;
}

int findLastRowLowPointRisk(int **map,int rows, int columns){
   int risk = 0;
   int i = rows-1;
   for(int j = 0; j<columns;j++){
            if(j==0){
                if(map[i][j] < map[i-1][j] &&
                    map[i][j]<map[i][j+1]){
                   risk = score(map,rows,columns,i,j);
             setMaxScore(risk);
                printf("d lowpoint (%i,%i) = %i\n",i,j,risk);
                }
            } else if(j==columns-1){
                //printf("b\n");
             if(map[i][j] < map[i-1][j] &&
                  map[i][j]<map[i][j-1]){
                  risk = score(map,rows,columns,i,j);
             setMaxScore(risk);
                printf("e lowpoint (%i,%i) = %i\n",i,j,risk);
             }
            } else {
                //printf("c\n");
             if(map[i][j] < map[i-1][j] &&
                  map[i][j]<map[i][j-1] &&
                  map[i][j]<map[i][j+1]){
                   risk = score(map,rows,columns,i,j);
             setMaxScore(risk);
                printf("f lowpoint (%i,%i) = %i\n",i,j,risk);
             }
            }
   }
   return risk==0?1:risk;
}

int findMiddleRowLowPointRisk(int **map,int rows, int columns,int row){
   int risk = 0;
   int i = row;
   for(int j = 0; j<columns;j++){
            if(j==0){
             if(map[i][j] < map[i-1][j] &&
                map[i][j] < map[i+1][j] &&
                  map[i][j]<map[i][j+1]){
                   risk = score(map,rows,columns,i,j);
             setMaxScore(risk);
                printf("g lowpoint (%i,%i) = %i\n",i,j,risk);
             }
            } else if(j==columns-1){
             if(map[i][j] < map[i-1][j] &&
                map[i][j] < map[i+1][j] &&
                  map[i][j]<map[i][j-1]){
                  risk = score(map,rows,columns,i,j);
             setMaxScore(risk);
                printf("h lowpoint (%i,%i) = %i\n",i,j,risk);
             }
            } else {
             if(map[i][j]<map[i-1][j] &&
                  map[i][j]<map[i+1][j] &&
                  map[i][j]<map[i][j-1] &&
                  map[i][j]<map[i][j+1]){
                   risk = score(map,rows,columns,i,j);
             setMaxScore(risk);
                printf("i lowpoint (%i,%i) = %i\n",i,j,risk);
             }
            }
   }
   return risk==0?1:risk;
}


int findLowPointRisk(int **map,int columns,int rows){
   int risk = 1;

   for(int i = 0; i<rows;i++){
       if(i == 0){
            // first row
            risk = findFirstRowLowPointRisk(map,rows,columns);
       } else if(i==rows-1){
              // last row
            risk = findLastRowLowPointRisk(map,rows,columns);
          } else {
              // general case;
            risk = findMiddleRowLowPointRisk(map,rows,columns,i);
          }
       //printf("%i risk %i\n",i,risk);
     }
    return risk;
}

int main(int argc,char **argv){

   list *input = stringList(argv[1]);
   //printList(input);
   int linelength= strlen(input->data[0]);
   //printf("before convert\n");
   int **map = convertInputToArrayOfInt(*input);
   //printf("after convert\n");
   int risk = findLowPointRisk(map,linelength,input->size);
   printf("low point risk %i\n",maxValues[0]*maxValues[1]*maxValues[2]);

   return 0;
}
