#include "common.h"

typedef struct __stackNode {
    char value;
    struct __stackNode *next;
} stackNode;

stackNode *stack = NULL;

void push(char c){
    stackNode *new = malloc(sizeof(stackNode));
    new->value=c;
    new->next=stack;
    stack=new;
}

char pop(){
    stackNode *top = stack;
    if(stack==NULL) return '\0';
    stack=stack->next;
    char value = top->value;
    free(top);
    return value;
}

void printStack(){
    stackNode *current=stack;
    while(current!=NULL){
        printf("%c",current->value);
        current=current->next;
    }
    printf("\n");
}

void clearStack(){
    while(stack!=NULL){
        pop();
    }
}

int lineScore(char *line){
    clearStack();
    //printf("%s\n",line);
    for(int i=0;i<strlen(line);i++){
        //printStack();
        char c;
        switch(line[i]){
            case '(':
            case '[':
            case '{':
            case '<': push(line[i]);
                      break;
            case ')':
                      c = pop();
                      if(c!='(') { 
                          //printf("%i matched %c to %c\n",i,c,line[i]);
                          return 3;
                      }
                      break;
            case ']': 
                      c = pop();
                      if(c!='[') { 
                          //printf("%i matched %c to %c\n",i,c,line[i]);
                          return 57;
                      }
                      break;
            case '}': 
                      c = pop();
                      if(c!='{') { 
                          //printf("%i matched %c to %c\n",i,c,line[i]);
                          return 1197;
                      }
                      break;
            case '>': 
                      c = pop();
                      if(c!='<') { 
                          //printf("%i matched %c to %c\n",i,c,line[i]);
                          return 25137;
                      }
                      break;
            case '\0': return 0;
            default: 
        }
    }
    return 0;
}

long remainderScore(){
    long score = 0;
    while(stack!=NULL){
        score = score*5;
        char c = pop();
        switch(c){
            case '(': score += 1;
                      break;
            case '[': score += 2;
                      break;
            case '{': score += 3;
                      break;
            case '<': score += 4;
                      break;
        }
    }
    return score;
}

void sort(long *array,int size){
    for(int i=0;i<size;i++){
        for(int j=1;j<size;j++)
            if(array[j-1]<array[j]){
                long temp=array[j];
                array[j]=array[j-1];
                array[j-1]=temp;
            }
    }
}

void printArray(long *array,int size){
    for(int i=0;i<size;i++)
        printf("%i %li\n",i,array[i]);
}

int main(int argc,char **argv){

   list *input = stringList(argv[1]);
   //printList(input);
   int total=0;
   long correctionsArray[1000];
   int totalCorrections=0;
   for(int i=0;i<input->size;i++){
       int score = lineScore(input->data[i]);
       if (score==0 & stack!=NULL){
           correctionsArray[totalCorrections]=remainderScore();
           totalCorrections++;
       }
   }

   sort(correctionsArray,totalCorrections);
   printArray(correctionsArray,totalCorrections);

   int middle=totalCorrections/2;

   printf("middle correction %li\n",correctionsArray[middle]);

   return 0;
}
