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

char *hexToBits(char *input){
    int binSize=4*strlen(input)+1;
    int bitPosition=0;
    char *bits = malloc(sizeof(char)*binSize);
    for(int i=0;i<strlen(input);i++){
        switch(input[i]) {
        case '0':
            bits[bitPosition++]='0';
            bits[bitPosition++]='0';
            bits[bitPosition++]='0';
            bits[bitPosition++]='0';
            break;
        case '1':
            bits[bitPosition++]='0';
            bits[bitPosition++]='0';
            bits[bitPosition++]='0';
            bits[bitPosition++]='1';
            break;
        case '2':
            bits[bitPosition++]='0';
            bits[bitPosition++]='0';
            bits[bitPosition++]='1';
            bits[bitPosition++]='0';
            break;
        case '3':
            bits[bitPosition++]='0';
            bits[bitPosition++]='0';
            bits[bitPosition++]='1';
            bits[bitPosition++]='1';
            break;
        case '4':
            bits[bitPosition++]='0';
            bits[bitPosition++]='1';
            bits[bitPosition++]='0';
            bits[bitPosition++]='0';
            break;
        case '5':
            bits[bitPosition++]='0';
            bits[bitPosition++]='1';
            bits[bitPosition++]='0';
            bits[bitPosition++]='1';
            break;
        case '6':
            bits[bitPosition++]='0';
            bits[bitPosition++]='1';
            bits[bitPosition++]='1';
            bits[bitPosition++]='0';
            break;
        case '7':
            bits[bitPosition++]='0';
            bits[bitPosition++]='1';
            bits[bitPosition++]='1';
            bits[bitPosition++]='1';
            break;
        case '8':
            bits[bitPosition++]='1';
            bits[bitPosition++]='0';
            bits[bitPosition++]='0';
            bits[bitPosition++]='0';
            break;
        case '9':
            bits[bitPosition++]='1';
            bits[bitPosition++]='0';
            bits[bitPosition++]='0';
            bits[bitPosition++]='1';
            break;
        case 'A':
            bits[bitPosition++]='1';
            bits[bitPosition++]='0';
            bits[bitPosition++]='1';
            bits[bitPosition++]='0';
            break;
        case 'B':
            bits[bitPosition++]='1';
            bits[bitPosition++]='0';
            bits[bitPosition++]='1';
            bits[bitPosition++]='1';
            break;
        case 'C':
            bits[bitPosition++]='1';
            bits[bitPosition++]='1';
            bits[bitPosition++]='0';
            bits[bitPosition++]='0';
            break;
        case 'D':
            bits[bitPosition++]='1';
            bits[bitPosition++]='1';
            bits[bitPosition++]='0';
            bits[bitPosition++]='1';
            break;
        case 'E':
            bits[bitPosition++]='1';
            bits[bitPosition++]='1';
            bits[bitPosition++]='1';
            bits[bitPosition++]='0';
            break;
        case 'F':
            bits[bitPosition++]='1';
            bits[bitPosition++]='1';
            bits[bitPosition++]='1';
            bits[bitPosition++]='1';
            break;
        }
    }
    bits[bitPosition]='\0';
    return bits;
}

