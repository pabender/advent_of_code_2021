#include "common.h"
#include "limits.h"

typedef struct __packet{
    int version;
    int type;
    char data[100];
    int subPacketCount;
    struct __packet *subPackets;
} packet;


int decodePacket(char *rawPacket,packet *onepacket);
int packetVersionSum(packet p);
void printPacket(packet p);
double calculate(packet packetValue);
