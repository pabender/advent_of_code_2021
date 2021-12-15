#include "common.h"
#include <limits.h>

int grid[1000][1000];
int xmax;
int ymax;
int minPaths[1000][1000];

void initGrid(list input){
    xmax=strlen(input.data[0]);
    ymax=input.size;
    for(int y=0;y<ymax;y++){
       for(int x=0;x<xmax;x++){
           grid[x][y]=input.data[y][x]-'0';
       }
    }
    for(int y=0;y<ymax;y++){
       for(int x=0;x<xmax;x++){
           minPaths[x][y]=-1;
       }
    }

    
}

int getMinPath(int x,int y,int goalx,int goaly){
    //    printf("%i %i\n",x,y);
    if(minPaths[x][y]>=0){
        return minPaths[x][y];
    }
    if(x==goalx && y==goaly) 
        return grid[x][y];
    else if((x+1)<xmax && (y+1)<ymax){
       minPaths[x][y]=min(grid[x+1][y]+getMinPath(x+1,y,goalx,goaly),
               grid[x][y+1]+getMinPath(x,y+1,goalx,goaly));
    } else if(x+1<xmax) {
        minPaths[x][y]=grid[x+1][y]+getMinPath(x+1,y,goalx,goaly);
    } else {
        minPaths[x][y]=grid[x][y+1]+getMinPath(x,y+1,goalx,goaly);
    }
    return minPaths[x][y];
}


int greedyMinPath(int x,int y,int goalx,int goaly){
    int score =0;
    int currentx = x;
    int currenty = y;
    while(currentx<xmax && currenty<ymax && !(x==goalx && y==goaly)){
        //printf("%i %i %i %i\n",currentx,currenty,grid[currentx][currenty],score);
        if(grid[currentx+1][currenty]<grid[currentx][currenty+1]){
            score += grid[currentx+1][currenty];
            currentx+=1;
        } else {
            score += grid[currentx][currenty+1];
            currenty+=1;
        }
    }
    return score;
}

int greedyReverseMinPath(){
    int score = grid[xmax-1][ymax-1];
    int currentx = xmax-1;
    int currenty = ymax-1;
    while(currentx>0 && currenty>0 ){
        //printf("%i %i %i %i\n",currentx,currenty,grid[currentx][currenty],score);
        if(grid[currentx-1][currenty]<grid[currentx][currenty-1]){
            score += grid[currentx-1][currenty];
            currentx-=1;
        } else {
            score += grid[currentx][currenty-1];
            currenty-=1;
        }
    }
    return score;
}

int main(int argc,char **argv){

   list *input = stringList(argv[1]);
   //printList(input);

   initGrid(*input);

   getMinPath(0,0,xmax-1,ymax-1);

   for(int y=0;y<ymax;y++){
       for(int x=0;x<xmax;x++){
           printf("%5i ",minPaths[x][y]);
       }
       printf("\n");
   }

   printf("min path %i\n",getMinPath(0,0,xmax-1,ymax-1));
   printf("greedy %i\n",greedyMinPath(0,0,xmax-1,ymax-1));
   printf("reverse greedy %i\n",greedyReverseMinPath());

   return 0;
}
