#include "common.h"

struct list{
    int size;
    char **data;
};

int oneCountInBitPosition(int bit,struct list data){
    int oneCount = 0;
    for(int i=0;i<data.size;i++){
      if(data.data[i][bit]=='1') oneCount++;
   } 
   return oneCount;
}

struct list *filterList(int bit,char filterChar,int resultCount,struct list data){
    struct list *retValue = malloc(sizeof(struct list));
    retValue -> size = resultCount;
    retValue -> data = malloc(sizeof(char *)*resultCount);

    
    int j=0;

    for(int i=0;i<data.size;i++){
       if(data.data[i][bit]==filterChar){
          retValue->data[j] = malloc(sizeof(char)*(strlen(data.data[i])+1));
          strcpy(retValue->data[j],data.data[i]);
          j++;
       } 
    }

    return retValue;
}

char *o2Rating(int bit,int bitlength,struct list data){
    int size = data.size;
    if(size==1){
        return data.data[0];
    }
    int oneCount = oneCountInBitPosition(bit,data);
    int zeroCount = size - oneCount;

    char searchChar ='1';
    int resultCount = oneCount;

    if(oneCount<zeroCount){
       searchChar = '0';
       resultCount = zeroCount;
    }

    struct list *smallerList = filterList(bit,searchChar,resultCount,data);

    return o2Rating(bit+1,bitlength,*smallerList);
}

char *co2Rating(int bit,int bitlength,struct list data){
    int size = data.size;
    if(size==1){
        return data.data[0];
    }
    int oneCount = oneCountInBitPosition(bit,data);
    int zeroCount = size - oneCount;

    char searchChar ='1';
    int resultCount = oneCount;

    if(oneCount>=zeroCount){
       searchChar = '0';
       resultCount = zeroCount;
    }

    struct list *smallerList = filterList(bit,searchChar,resultCount,data);

    return co2Rating(bit+1,bitlength,*smallerList);
}


struct list *stringList(char *fileName){
    char buffer[10000];
    char **retValue;
    FILE *f = fopen(fileName,"r");
    int rows = 0;

    fscanf(f,"%s",&buffer);
    do {
        rows++;
        fscanf(f,"%s",&buffer);
    } while(!feof(f));

    fseek(f,0,SEEK_SET);

    retValue = malloc(sizeof(char *)*rows);
    
    for(int i=0;i<rows;i++){
       fscanf(f,"%s",&buffer);
       retValue[i] = malloc(sizeof(char)*(strlen(buffer)+1));
       strcpy(retValue[i],buffer); 
    }

    fclose(f);

    struct list *value = malloc(sizeof(struct list));
    value->size = rows;
    value->data = retValue;
    return value;
}

void printList(struct list *data){
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

int main(int argc,char **argv){

    struct list *inputList = stringList(argv[1]); 
    int bitlength;
    //printList(inputList);

    bitlength = strlen(inputList->data[0]);

    int o2 = bitsToInt(o2Rating(0,bitlength,*inputList));
    int co2 = bitsToInt(co2Rating(0,bitlength,*inputList));

    printf( "o2 %i, co2 %i, product %i\n",
            o2,co2,o2*co2);
   return 0;
}
