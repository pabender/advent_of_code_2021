#include "common.h"

#define true 1
#define false 0;

typedef struct __octopus{
    int energy_level;
    int highlighted;
} octopus;

void initGrid(octopus grid[10][10],list input){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            grid[i][j].energy_level=input.data[i][j]-'0';
            grid[i][j].highlighted=false;
        }
    }
}

int resetHighLighted(octopus grid[10][10]){
    int count =0;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(grid[i][j].highlighted==true){
               grid[i][j].highlighted=false;
               count+=1;
            }
        }
    }
    return count;
}

void incrementOctopus(octopus grid[10][10],int x,int y){
    if(x<0 || x>9 || y<0 || y>9) return;
    if(grid[x][y].highlighted==true) return;
    grid[x][y].energy_level++;
    if(grid[x][y].energy_level>9){
        grid[x][y].energy_level=0;
        grid[x][y].highlighted=true;
        for(int i=x-1;i<=(x+1);i++) {
           for(int j=y-1;j<=(y+1);j++) {
               incrementOctopus(grid,i,j);
           }
        }
    }

}

int simulate(octopus grid[10][10]){
    int flashes = 0;
    for(int i=0;i<10000;i++){
        for(int j=0;j<10;j++){
            for(int k=0;k<10;k++){
                incrementOctopus(grid,j,k);
            }
        }
        flashes = resetHighLighted(grid);
        if(flashes==100) return i+1;
    }
    return -1;
}


int main(int argc,char **argv){

   list *input = stringList(argv[1]);
   //printList(input);

   octopus grid[10][10];
   initGrid(grid,*input);

   int flashes = simulate(grid);

   printf("flashes %i\n",flashes);

   return 0;
}
