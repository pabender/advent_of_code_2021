#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATASIZE 10000

#define min(x,y) x>y?y:x
#define max(x,y) x<y?y:x

typedef struct data_list {
    int size;
    char **data;
} list;

list *stringList(char *fileName);
void printList(list *data);
int bitsToInt(char *bits);
unsigned long long bitsToLLU(char *bits);
int *stringToIntArray(char *input);
int getArraySize();
char *hexToBits(char *input);
#endif
