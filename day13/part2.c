#include "common.h"

int paper[2000][2000];
int maxx=0;
int maxy=0;

typedef struct __inst{
    char folddir;
    int position;
    struct __inst* next;
} instruction;

instruction *instructions;

void parseInput(list input){
   int i=0;
   while(i<input.size){
      //printf("%s\n",input.data[i]);
       int *dot = stringToIntArray(input.data[i]);
       if(getArraySize()!=2) {
           break;
       }
       maxx=max(dot[0],maxx);
       maxy=max(dot[1],maxy);
       //printf("%i %i\n",maxx,maxy);
       paper[dot[0]][dot[1]]=1;
       i++;
   }
  
   instructions=NULL;
   instruction *current;

   while(i<input.size) {
      // printf("start %i %i\n",input.size,i);
      //printf("%s\n",input.data[i]);
      char dir[2];
      int pos;

      int values = sscanf(input.data[i]," fold along %[^=]=%i",&dir,&pos);
      //printf("converted %i %s %i\n",values,dir,pos);

      //printf("after scanf\n");

      if(instructions==NULL){
         instructions=malloc(sizeof(instruction));
         instructions->folddir=dir[0];
         instructions->position=pos;
         instructions->next=NULL;
         current=instructions;
      } else {
         current->next=malloc(sizeof(instruction));
         current->next->folddir=dir[0];
         current->next->position=pos;
         current->next->next=NULL;
         current=current->next;
      }
      i++;
   }
   //printf("loop end\n");
}

void printPaper(){
   for(int i=0;i<=maxy;i++){
      for(int j=0;j<=maxx;j++){
          if(paper[j][i]==1) {
              printf("%c",219);
          } else {
              printf(" ");
          }
      }
      printf("\n");
   }
}

int countDots(){
    int count =0;
   for(int i=0;i<=maxy;i++){
      for(int j=0;j<=maxx;j++){
         if(paper[j][i]==1) count++;
      }
   }
   return count;
}

void foldx(int position){
    for(int i=0;i<=position;i++)
        for(int j=0;j<=maxy;j++){
            if(paper[i][j]==1 || paper[maxx-i][j]==1){
                //printf("set position (%i,%i)\n",i,j);
                paper[i][j]=1;
            } else {
                paper[i][j]=0;
            }
        }
    maxx=position-1;
}

void foldy(int position){
    for(int j=0;j<=position;j++)
        for(int i=0;i<=maxx;i++){
            if(paper[i][j]==1 || paper[i][maxy-j]==1){
                //printf("set position (%i,%i)\n",i,j);
                paper[i][j]=1;
            } else {
                paper[i][j]=0;
            }
        }
    maxy=position-1;
}

void fold(char direction,int position){
   //printf("fold %c %i\n",direction,position);
   if(direction=='x'){
       foldx(position);
   } else {
       foldy(position);
   }
}

void printInstructions(){
    instruction *current=instructions;
    while(current!=NULL){
        printf("%c %i\n",current->folddir,current->position);
        current=current->next;
    }
}

void allFolds(){
    instruction *current=instructions;
    int foldcount=0;
    while(current!=NULL){
    //    printf("%i maxx: %i maxy: %i\n",foldcount,maxx,maxy);
        foldcount++;
      fold(current->folddir,current->position);
      current=current->next;

    }
    //    printf("%i maxx: %i maxy: %i\n",foldcount,maxx,maxy);
}

int main(int argc,char **argv){

   list *input = stringList(argv[1]);
   //printList(input);

   parseInput(*input);
   //printPaper();
   //printInstructions();

   //printf("before fold\n");
   allFolds();
   printPaper();
   //printf("after fold\n");

   printf("number of dots %i\n",countDots());

   return 0;
}
