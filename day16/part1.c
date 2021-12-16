#include "common.h"

typedef struct __packet{
    int version;
    int type;
    char data[256];
    int subPacketCount;
    struct __packet *subPackets;
} packet;


int decodePacket(char *rawPacket,packet *onepacket);

int decodePackets(char *input,packet *packetArray){
    int bitsConsumed=0;
    int numPacketsConsumed=0;
    while(bitsConsumed<(strlen(input)-4)){
        //printf("decode packets %i bits %i\n",numPacketsConsumed,bitsConsumed);
        bitsConsumed+=decodePacket(input+bitsConsumed
                ,packetArray+numPacketsConsumed);
        numPacketsConsumed++;
    }
        //printf("decoded packets %i bits %i\n",numPacketsConsumed,bitsConsumed);
    return numPacketsConsumed;
}

int decodeSubPackets(char *input,packet *packetArray){
    int bitsConsumed=0;
    int numPacketsConsumed=0;
    while(bitsConsumed<strlen(input)){
        //printf("decode packets %i bits %i\n",numPacketsConsumed,bitsConsumed);
        bitsConsumed+=decodePacket(input+bitsConsumed,packetArray+numPacketsConsumed);
        numPacketsConsumed++;
    }
        //printf("decoded packets %i bits %i\n",numPacketsConsumed,bitsConsumed);
    return numPacketsConsumed;
}

int decodeNPackets(char *input,packet *packetArray,int count){
    int bitsConsumed=0;
    int numPacketsConsumed = 0;
    while(numPacketsConsumed<count){
        printf("decode %i packets %i bits %i\n",count,numPacketsConsumed,bitsConsumed);
        bitsConsumed+=decodePacket(input+bitsConsumed,packetArray+numPacketsConsumed);
        numPacketsConsumed++;
    }
    printf("decoded %i packets %i bits %i\n",count,numPacketsConsumed,bitsConsumed);
    return bitsConsumed;
}


int decodePacket(char *rawPacket,packet *onepacket){

    printf("raw packet %s\n",rawPacket);

    char versionString[4];
    versionString[0]=rawPacket[0];
    versionString[1]=rawPacket[1];
    versionString[2]=rawPacket[2];
    versionString[3]='\0';
    onepacket->version=bitsToInt(versionString);

    char typeString[4];
    typeString[0]=rawPacket[3];
    typeString[1]=rawPacket[4];
    typeString[2]=rawPacket[5];
    typeString[3]='\0';

    onepacket->type=bitsToInt(typeString);
    onepacket->subPacketCount=0;

    //printf("next packet %i %i\n",onepacket->version,onepacket->type);

    int i=6;
    switch(onepacket->type){
        case 4:{
                   printf("litteral\n");
                   // litteralValue
                   int dataCount=0;
                   // read groups of 5 bits;
                  
                   char stopBit='0';
                   do{ 
                      stopBit = rawPacket[i];
                      onepacket->data[dataCount++]=rawPacket[i+1];
                      onepacket->data[dataCount++]=rawPacket[i+2];
                      onepacket->data[dataCount++]=rawPacket[i+3];
                      onepacket->data[dataCount++]=rawPacket[i+4];
                      onepacket->data[dataCount]='\0';
                      i=i+5;
                   } while(stopBit!='0');
               }
               break;
        default: {
                     printf("operator\n");
                     //operator packet
                     char lengthType = rawPacket[i];
                     i=i+1;
                     if(lengthType=='0'){
                         //next 15 bits represent the 
                         //number of bits for sub packets
                         printf("sub packet type 0 %c\n",lengthType);
                         char subPacketLengthBits[16];
                         for(int j=0;j<15;j++){
                             subPacketLengthBits[j]=rawPacket[i];
                             i++;
                         }
                         subPacketLengthBits[15]='\0';
                         printf("%s\n%",subPacketLengthBits);
                         int subPacketLength=bitsToInt(subPacketLengthBits);
                         printf("sub packet length %i\n",subPacketLength);

                         for(int j=0;j<subPacketLength;j++){
                            onepacket->data[j]=rawPacket[i];
                            i++;
                         }
                         onepacket->data[subPacketLength]='\0';
                         onepacket->subPackets=malloc(sizeof(packet)*10);
                         onepacket->subPacketCount = 
                             decodeSubPackets(onepacket->data,
                                     onepacket->subPackets);
                         //printf("%i\n",onepacket->subPacketCount);
                         i+=subPacketLength;

                     }
                     else { //lengthType=1
                         //next 11 bits represent the number of
                         //sub packes contained in this packet
                         printf("sub packet type 1\n");
                         char subPacketCountBits[12];
                         for(int j=0;j<11;j++){
                             subPacketCountBits[j]=rawPacket[i];
                             i++;
                         }
                         subPacketCountBits[11]='\0';
                         int subPacketCount=bitsToInt(subPacketCountBits);
                         onepacket->subPacketCount = subPacketCount;
                         onepacket->subPackets=malloc(sizeof(packet)*10);
                         printf("%i %i %s\n",strlen(rawPacket),i,rawPacket+i);
                         i+=decodeNPackets(rawPacket+i,
                                     onepacket->subPackets,subPacketCount);
                         printf("%i %i %s\n",strlen(rawPacket),i,rawPacket+i);
                         //printf("%i\n",onepacket->subPacketCount);
                     }
                 }
    }
    //printf("decode complete\n");
    return i;
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

int packetVersionSum(packet *packetArray,int packetCount){
    int sum=0;
    //printf("packetCount %i\n",packetCount);
    for(int i=0;i<packetCount;i++){
        sum+=packetArray[i].version;
        if(packetArray[i].subPacketCount>0){
            sum+=packetVersionSum(packetArray[i].subPackets,
                    packetArray[i].subPacketCount);
        }
    }
    return sum;
}

int printPackets(packet *packetArray,int packetCount){
    for(int i=0;i<packetCount;i++){
        printf("Packet %i version %i type %i subPacketCount %i\n",
                i,packetArray[i].version,packetArray[i].type,packetArray[i].subPacketCount);
        if(packetArray[i].subPacketCount>0){
            printf("subPackets: \n");
            printPackets(packetArray[i].subPackets,packetArray[i].subPacketCount);
            printf("end subPackets: \n");
        }
    }
}

int main(int argc,char **argv){

   int numPackets=0;

   packet packets[2000];

   list *input = stringList(argv[1]);
   //printList(input);

   char *bits = hexToBits(input->data[0]);
   //printf("%s\n",bits);

   numPackets += decodePackets(bits,packets);
   //printf("all decoded\n");
   
   printPackets(packets,numPackets);

   printf("version sum: %i\n",packetVersionSum(packets,numPackets));

   return 0;
}
