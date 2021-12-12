#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATASIZE 10000

typedef struct data_list {
    int size;
    char **data;
} list;

list *stringList(char *fileName);
void printList(list *data);
int bitsToInt(char *bits);
