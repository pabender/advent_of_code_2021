#include "common.h"

#define GRIDSIZE 1000

void initGrid(int grid[GRIDSIZE][GRIDSIZE]){
    for(int x=0;x<GRIDSIZE;x++){
        for(int y=0;y<GRIDSIZE;y++){
            grid[x][y]=0;
        }
    }
}

void plot(int x1,int y1,int x2,int y2,int grid[GRIDSIZE][GRIDSIZE]){
    if(x1==x2){
      int miny = min(y1,y2);
      int maxy = max(y1,y2);
      for(int y=miny;y<=maxy;y++){
          grid[x1][y]++;
      }
    }
    else if(y1==y2){
        int minx = min(x1,x2);
        int maxx = max(x1,x2);
        for(int x=minx;x<=maxx;x++){
          grid[x][y1]++;
        }
    }
    else {
        // y = (y2 -y1)/x2-x1)(x-x1) +y1
        int minx = min(x1,x2);
        int maxx = max(x1,x2);
        for(int x=minx;x<=maxx;x++){
            int y = ((y2 -y1)/(x2-x1))*(x-x1)+y1;
          grid[x][y]++;
        }
         
    }

}

void plotLines(int grid[GRIDSIZE][GRIDSIZE],list input){
   int x1,x2,y1,y2;
   for(int i=0;i<input.size;i++){
       sscanf(input.data[i]," %i,%i -> %i,%i",&x1,&y1,&x2,&y2);
       plot(x1,y1,x2,y2,grid);
   }

}

int hotspotCount(int grid[GRIDSIZE][GRIDSIZE], int threshold){
    int hotspots = 0;
    for(int x=0;x<GRIDSIZE;x++){
        for(int y=0;y<GRIDSIZE;y++){
            if(grid[x][y] >= threshold)
                hotspots++;
        }
    }
    return hotspots;
}


void printGridSnapshot(int grid[GRIDSIZE][GRIDSIZE]){
    for(int x=0;x<12;x++){
        for(int y=0;y<12;y++){
            printf("%i",grid[x][y]);
        }
        printf("\n");
    }
}

int main(int argc,char **argv){

   int grid[GRIDSIZE][GRIDSIZE];
   int threshold = 2;

   initGrid(grid);

   list *input = stringList(argv[1]);
   //printList(input);

   plotLines(grid,*input);
   printGridSnapshot(grid);
   printf("hotspots %i\n",hotspotCount(grid,threshold));


   return 0;
}
