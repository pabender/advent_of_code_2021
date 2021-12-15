#include "common.h"
#include <limits.h> 
#include <float.h> 

typedef struct __replacement{
    char match[3];
    char insert[2];
    unsigned long long count;
} replacement;

char *result;

replacement replacements[1000];

int numReplacements;
unsigned long long frequencies[26];

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
        printf("%s -> %s %llu\n",replacements[i].match,replacements[i].insert,replacements[i].count);
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

void incMatch(char *buffer,unsigned long long size){
    for(int i=0;i<numReplacements;i++){
        if(strcmp(buffer,replacements[i].match)==0){
            printf("inc %s by %llu\n",buffer,size);
            replacements[i].count += size;
            break;
        }
    }
}

unsigned long long matchCount(char *buffer){
    for(int i=0;i<numReplacements;i++){
        if(strcmp(buffer,replacements[i].match)==0){
            return replacements[i].count;
        }
    }
    return 0;
}

void initReplace(){
    for(int i=0;i<strlen(result)-1;i++){
        char buffer[3];
        strncpy(buffer,result+i,2);
        buffer[2]='\0';
        int match=findMatch(buffer);
        frequencies[result[i]-'A']+=1;
        if(match>0) {
            incMatch(buffer,1);
        }
    }
    frequencies[result[strlen(result)-1]-'A']+=1;
}

void replace(){
    int oldCounts[1000];
    for(int i=0;i<numReplacements;i++){
        oldCounts[i]=replacements[i].count;
    }
    for(int i=0;i<numReplacements;i++){
        if(oldCounts[i]>0) {
            //printf("replace %s with %s count %i\n",replacements[i].match,
            //        replacements[i].insert,oldCounts[i]);
           unsigned long long count = oldCounts[i];
           replacements[i].count-=count;
           char firstPair[3];
           firstPair[0]=replacements[i].insert[0];
           firstPair[1]=replacements[i].match[1];
           firstPair[2]='\0';
           char secondPair[3];
           secondPair[0]=replacements[i].match[0];
           secondPair[1]=replacements[i].insert[0];
           secondPair[2]='\0';
           incMatch(firstPair,count);
           incMatch(secondPair,count);
           printf("inc %c by %llu\n",replacements[i].insert[0],count);
           frequencies[replacements[i].insert[0]-'A']+=count;
        }
    }
}


void printFrequencies(){
    for(int i=0;i<26;i++){
        printf("%c %llu\n",'A'+i,frequencies[i]);
    }
}

unsigned long long maxFrequency(){
    unsigned long long maxf=0;
    for(int i=0;i<26;i++){
        maxf=max(maxf,frequencies[i]);
    }
    return maxf;
}

unsigned long long minFrequency(){
    unsigned long long minf=LONG_MAX;
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
   initReplace();
   //printReplacements();
   //printFrequencies();

   for(int i=0;i<40;i++) {
      replace();
   }

   printReplacements();
   printFrequencies();

   printf("min %llu max %llu difference %llu\n",minFrequency(),maxFrequency(),maxFrequency()-minFrequency());

   return 0;
}
