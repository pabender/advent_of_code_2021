#include "common.h"

int main(int argc,char **argv){

   int cubes[101][101][101];
   for(int x=0;x<101;x++){
      for(int y=0;y<101;y++){
         for(int z=0;z<101;z++){
             cubes[x][y][z]=0;
         }
      }
   }

   list *input = stringList(argv[1]);
   //printList(input);

   for(int i=0;i<input->size;i++){
       char cmd[5];
       int xmin,xmax,ymin,ymax,zmin,zmax;
       sscanf(input->data[i]," %s x=%i..%i,y=%i..%i,z=%i..%i",
               &cmd,&xmin,&xmax,&ymin,&ymax,&zmin,&zmax);
       for(int x=xmin;x<=xmax;x++){
          for(int y=ymin;y<=ymax;y++){
              for(int z=zmin;z<=zmax;z++){
                  if(x>=-50 && x<=50 && 
                          y>=-50 && y<=50 && 
                            z>=-50 && y<=50) {
                     if(strcmp(cmd,"on")==0){
                         //printf("%i %i %i\n",x,y,z);
                         cubes[x+50][y+50][z+50]=1;
                     } else {
                         cubes[x+50][y+50][z+50]=0;
                     }
                  }
              }
          }
       }
   }

   int count=0;

   for(int x=0;x<101;x++){
      for(int y=0;y<101;y++){
         for(int z=0;z<101;z++){
             if(cubes[x][y][z]==1){
                 count++;
             }
         }
      }
   }

   printf("cubes on %i\n",count);

   return 0;
}
