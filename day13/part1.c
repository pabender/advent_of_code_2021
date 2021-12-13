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
      instruction *temp=malloc(sizeof(instruction));
      char dir[2];
      int pos;

      int values = sscanf(input.data[i]," fold along %[^=]=%i",&dir,&pos);
      printf("converted %i %s %i",values,dir,pos);
      temp->folddir=dir[0];
      temp->position=pos;
      temp->next=NULL;

      //printf("after scanf\n");

      //printf("%p\n",instructions);

      if(instructions==NULL){
         temp->next=instructions;
         instructions=temp;
         current=temp;
      } else {
         current->next=temp;
         current=temp;
      }
      i++;
   }
   //printf("loop end\n");
}

void printPaper(){
   for(int i=0;i<=maxy;i++){
      for(int j=0;j<=maxx;j++){
         printf("%i",paper[j][i]);
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
            }
        }
    maxy=position-1;
}

void fold(char direction,int position){
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
    fold(instructions->folddir,instructions->position);
}

int main(int argc,char **argv){

   list *input = stringList(argv[1]);
   //printList(input);

   parseInput(*input);
   //printPaper();
   printInstructions();

   //printf("before fold\n");
   allFolds();
   //printPaper();
   //printf("after fold\n");

   printf("number of dots %i\n",countDots());

   return 0;
}
