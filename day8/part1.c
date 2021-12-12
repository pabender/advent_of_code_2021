#include "common.h"

int main(int argc,char **argv){

   list *input = stringList(argv[1]);
   //printList(input);

   int count = 0;

   printf("size %i\n",input->size);
   for(int i=0;i<input->size;i++){
       char *current = strtok(input->data[i],"|");
       current = strtok(NULL," ");
       do {
         int length = strlen(current);
         if(length == 2 || length == 3 || length == 4 || length == 7){
             printf("%s\n",current);
             count++;
         }
         current = strtok(NULL," ");
       } while( current!=NULL);
       printf("%i count %i\n",i,count);
   }

   printf("count %i\n",count);

   return 0;
}
