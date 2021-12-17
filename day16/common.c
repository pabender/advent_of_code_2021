#include "common.h"

list *stringList(char *fileName){
    char buffer[DATASIZE];
    char **retValue;
    FILE *f = fopen(fileName,"r");
    int rows = 0;

    fscanf(f," %[^\n]",&buffer);
    do {
        rows++;
        fscanf(f," %[^\n]",&buffer);
    } while(!feof(f));

    fseek(f,0,SEEK_SET);

    retValue = malloc(sizeof(char *)*rows);
    
    for(int i=0;i<rows;i++){
       fscanf(f, " %[^\n]",&buffer);
       retValue[i] = malloc(sizeof(char)*(strlen(buffer)+1));
       strcpy(retValue[i],buffer); 
    }

    fclose(f);

    list *value = malloc(sizeof(list));
    value->size = rows;
    value->data = retValue;
    return value;
}

void printList(list *data){
    for(int i=0;i<data->size;i++){
        printf("%s\n",data->data[i]);
    }
}

int bitsToInt(char *bits){
    int result = 0;
    int bitlength = strlen(bits);
    for(int i=0;i<bitlength;i++){
        if(bits[i]=='1')
          result |= (0x01<<((bitlength-1)-i));
    }
        return result;
}

unsigned long long bitsToLLU(char *bits){
    unsigned long long result = 0;
    int bitlength = strlen(bits);
    for(int i=0;i<bitlength;i++){
        if(bits[i]=='1')
          result |= (0x01<<((bitlength-1)-i));
    }
        return result;
}

static int arraySize;

int *stringToIntArray(char *input){
    int *array = malloc(sizeof(int)*DATASIZE);
    int current=0;
    char *nextValue = strtok(input,",");
    while(nextValue!=NULL){
        array[current++]=atoi(nextValue);
        nextValue = strtok(NULL,",");
    }
    printf("array count %i\n",current);
    arraySize = current;
    return array;
}

int getArraySize(){
    return arraySize;
}
