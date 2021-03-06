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
