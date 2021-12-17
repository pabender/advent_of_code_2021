#include "common.h"
#include <limits.h>

typedef struct __target {
    int xmin;
    int xmax;
    int ymin;
    int ymax;
} target;

typedef struct __point{
    int x;
    int y;
} point;

point positionAfterStep(int step,int initialXSpeed, int initialYSpeed){
    point finalPosition;
    finalPosition.x=0;
    finalPosition.y=0;
    int xspeed = initialXSpeed;
    int yspeed = initialYSpeed;
    for(int i=0;i<step;i++){
        finalPosition.x=finalPosition.x+xspeed;

        finalPosition.y=finalPosition.y+yspeed;

        if(xspeed>0){
            xspeed= xspeed -1;
        } else if(xspeed<0){
            xspeed=xspeed +1;
        }

        yspeed = yspeed -1;
    }
    return finalPosition;
}

int inTargetArea(point p,target t){
    //printf("t.xmin %i p.x %i t.xmax %i\n",t.xmin,p.x,t.xmax);
    //printf("t.ymin %i p.y %i t.ymin %i\n",t.ymin,p.y,t.ymax);
    if( p.x <= t.xmax && p.x >= t.xmin && p.y>=t.ymin && p.y<=t.ymax){
        return 1;
    }
    return 0;
}

int pastTargetArea(point p,target t){
    if( p.x > t.xmax || p.y<t.ymin ){
        return 1;
    }
    return 0;
}

int hit(int xspeed,int yspeed,target t){
   point p;
   p.x=0;
   p.y=0;
   int step=0;
   do {
     p=positionAfterStep(step,xspeed,yspeed);
     step++;
   } while(pastTargetArea(p,t)!=1 && inTargetArea(p,t)!=1);
   return inTargetArea(p,t);
}

int maxYPosition(int xspeed,int yspeed,target t){
   point p;
   p.x=0;
   p.y=0;
   int step=0;
   int maxy=0;
   do {
     p=positionAfterStep(step,xspeed,yspeed);
     step++;
     maxy=max(maxy,p.y);
     //printf("(%i,%i)\n",p.x,p.y);
   } while(pastTargetArea(p,t)!=1 && inTargetArea(p,t)!=1);
   return maxy;
}


int main(int argc,char **argv){

   target t;

   list *input = stringList(argv[1]);
   printList(input);

   sscanf(input->data[0],"target area: x=%i..%i, y=%i..%i",&t.xmin,&t.xmax,&t.ymin,&t.ymax);

   int maxy=-1*INT_MAX;

   for(int x=0;x<=t.xmax;x++){
       for(int y=-10;y<1000;y++){
           int targethit = hit(x,y,t);
           int yvalue = maxYPosition(x,y,t); 
           if(targethit==1){
              maxy=max(maxy,yvalue);
              printf("xspeed %i, yspeed %i %s, max y %i\n",x,y,targethit==1?"hit":"miss",yvalue);

           }
       }
   }
   printf("max y %i\n",maxy);
   //printf("max y for 6,9 %i %i\n",maxYPosition(6,9,t),hit(6,9,t));
   
   return 0;
}
