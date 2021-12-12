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
                          printf("%i matched %c to %c\n",i,c,line[i]);
                          return 3;
                      }
                      break;
            case ']': 
                      c = pop();
                      if(c!='[') { 
                          printf("%i matched %c to %c\n",i,c,line[i]);
                          return 57;
                      }
                      break;
            case '}': 
                      c = pop();
                      if(c!='{') { 
                          printf("%i matched %c to %c\n",i,c,line[i]);
                          return 1197;
                      }
                      break;
            case '>': 
                      c = pop();
                      if(c!='<') { 
                          printf("%i matched %c to %c\n",i,c,line[i]);
                          return 25137;
                      }
                      break;
            case '\0': return 0;
            default: 
        }
    }
    return 0;
}

int main(int argc,char **argv){

   list *input = stringList(argv[1]);
   //printList(input);
   int total=0;
   for(int i=0;i<input->size;i++){
       total += lineScore(input->data[i]);
   }

   printf("total %i\n",total);

   return 0;
}
