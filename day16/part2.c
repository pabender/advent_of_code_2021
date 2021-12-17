#include "common.h"
#include <limits.h>
#include "decoder.h"

int main(int argc,char **argv){

   packet p;

   list *input = stringList(argv[1]);
   //printList(input);

   char *bits = hexToBits(input->data[0]);
   //printf("%s\n",bits);

   decodePacket(bits,&p);
   //printf("all decoded\n");
   
   //printPacket(p);

   //printf("num packets %i\n",numPackets);

   //printf("Packet version sum %i\n",packetVersionSum(p));
   printf("calculated value %f\n",calculate(p));
   return 0;
}
