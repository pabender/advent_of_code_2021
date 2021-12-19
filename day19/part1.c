#include "common.h"
#include "point.h"

int main(int argc,char **argv){

   list *input = stringList(argv[1]);
   printList(input);

   return 0;
}
