#include "common.h"
#include <limits.h> 
#include <unistd.h> 

typedef struct __replacement{
    char match[3];
    char insert[2];
} replacement;

char *result;

FILE *resultFile;
FILE *output;

replacement replacements[100];

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

void replace(char *inFileName,char *outFileName){
    //printf("%s %s\n",inFileName,outFileName);
    FILE *infile=fopen(inFileName,"r");
    FILE *outfile=fopen(outFileName,"w");
    char buffer[3];

    buffer[1]=fgetc(infile);
    while(!feof(infile)) {
        buffer[0]=buffer[1];
        fputc(buffer[0],outfile);
        buffer[1]=fgetc(infile);
        buffer[2]='\0';
        int match=findMatch(buffer);
        if(match>0){
           fputc(match,outfile);
        }
    }
    fputc(buffer[1],outfile);
    fclose(infile);
    fclose(outfile);
    unlink(infile);
}

unsigned long frequencies[26];

void findFrequencies(char *fileName){
    FILE *infile=fopen(fileName,"r");
    while(!feof(infile)){
        int in=fgetc(infile);
        frequencies[in -'A']++;
    }
    fclose(infile);
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

   //printf("%s\n",result);
   //printReplacements();
   FILE *temp = fopen("temp0","w");
   fprintf(temp,"%s",result);
   fclose(temp);

   for(int i=1;i<=40;i++) {
       printf("%i\n",i);
      char infilename[10];
      char outfilename[10];

      sprintf(infilename,"temp%i",i-1);
      sprintf(outfilename,"temp%i",i);

      replace(infilename,outfilename);
      //printf("%s\n",result);
   }
   printf("result found\n");

   findFrequencies("temp40");
   //printFrequencies();

   printf("min %i max %i difference %i\n",minFrequency(),maxFrequency(),maxFrequency()-minFrequency());

   return 0;
}
