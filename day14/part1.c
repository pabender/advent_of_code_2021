#include "common.h"
#include <limits.h> 

typedef struct __replacement{
    char match[3];
    char insert[2];
} replacement;

char *result;

replacement replacements[1000];

int numReplacements;

void parseInput(list input){
    char *buffer=malloc(sizeof(char)*(strlen(input.data[0])+1));
    strcpy(buffer,input.data[0]);
    result = buffer;

    for(int i=1;i<input.size;i++){
        sscanf(input.data[i]," %2s -> %1s",&replacements[i-1].match,&replacements[i-1].insert);
    }

    numReplacements=input.size-1;
}

void printReplacements(){
    for(int i=0;i<numReplacements;i++){
        printf("%s -> %s\n",replacements[i].match,replacements[i].insert);
    }
}

int findMatch(char *buffer){
    for(int i=0;i<numReplacements;i++){
        if(strcmp(buffer,replacements[i].match)==0){
            return replacements[i].insert[0];
        }
    }
    return -1;
}

void replace(){
    char *temp=malloc(sizeof(char)*strlen(result)*strlen(result));
    int outputLength=0;
    for(int i=0;i<strlen(result)-1;i++){
        temp[outputLength++]=result[i];
        char buffer[3];
        strncpy(buffer,result+i,2);
        buffer[2]='\0';
        int match=findMatch(buffer);
        if(match>0){
           temp[outputLength++]=match;
        }
    }
    temp[outputLength]=result[strlen(result)-1];
    temp[outputLength+1]='\0';
    result=temp;
}

int frequencies[26];

void findFrequencies(){
    for(int i=0;i<strlen(result);i++){
        frequencies[result[i]-'A']++;
    }
}

void printFrequencies(){
    for(int i=0;i<26;i++){
        printf("%c %i\n",'A'+i,frequencies[i]);
    }
}

int maxFrequency(){
    int maxf=0;
    for(int i=0;i<26;i++){
        maxf=max(maxf,frequencies[i]);
    }
    return maxf;
}

int minFrequency(){
    int minf=INT_MAX;
    for(int i=0;i<26;i++){
        if(frequencies[i]!=0) {
           minf=min(minf,frequencies[i]);
        }
    }
    return minf;
}

int main(int argc,char **argv){

   list *input = stringList(argv[1]);
   //printList(input);

   parseInput(*input);

   printf("%s\n",result);
   printReplacements();
   for(int i=0;i<10;i++) {
      replace();
      printf("%s\n",result);
   }

   findFrequencies();
   printFrequencies();

   printf("min %i max %i difference %i\n",minFrequency(),maxFrequency(),maxFrequency()-minFrequency());

   return 0;
}
