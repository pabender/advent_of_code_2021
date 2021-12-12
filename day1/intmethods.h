#include <stdio.h>
#include <stdlib.h>

#define DATASIZE 10000

int *getIntArray(char *filename);
int countChangesInArray(int *array,int (*f)(int *,int),int startPos);
