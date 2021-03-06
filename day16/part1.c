#include "common.h"

typedef struct __packet{
    int version;
    int type;
    char data[100];
    int subPacketCount;
    struct __packet *subPackets;
} packet;


int decodePacket(char *rawPacket,packet *onepacket);

int decodePackets(char *input,packet *packetArray){
    int bitsConsumed=0;
    int numPacketsConsumed=0;
    while(bitsConsumed<(strlen(input)-8)){
        //printf("decode packets %i bits %i\n",numPacketsConsumed,bitsConsumed);
        bitsConsumed+=decodePacket(input+bitsConsumed
                ,packetArray+numPacketsConsumed);
        numPacketsConsumed++;
        //printf("decode packets %i bits %i\n",numPacketsConsumed,bitsConsumed);
    }
        //printf("decoded packets %i bits %i\n",numPacketsConsumed,bitsConsumed);
    return numPacketsConsumed;
}

int decodeSubPackets(char *input,packet *packetArray){
    int bitsConsumed=0;
    int numPacketsConsumed=0;
    while(bitsConsumed<strlen(input)){
       printf("decode packets %i bits %i\n",numPacketsConsumed,bitsConsumed);
        bitsConsumed+=decodePacket(input+bitsConsumed,packetArray+numPacketsConsumed);
        numPacketsConsumed++;
        //printf("decode packets %i bits %i\n",numPacketsConsumed,bitsConsumed);
    }
        //printf("decoded packets %i bits %i\n",numPacketsConsumed,bitsConsumed);
    return numPacketsConsumed;
}

int decodeNPackets(char *input,packet *packetArray,int count){
    int bitsConsumed=0;
    int numPacketsConsumed = 0;
    while(numPacketsConsumed<count){
        //printf("decode %i packets %i bits %i\n",count,numPacketsConsumed,bitsConsumed);
        //printf("%s\n",input+bitsConsumed);
	bitsConsumed+=decodePacket(input+bitsConsumed,packetArray+numPacketsConsumed);
        numPacketsConsumed++;
    }
    //printf("decoded %i packets %i bits %i\n",count,numPacketsConsumed,bitsConsumed);
    return bitsConsumed;
}


int decodePacket(char *rawPacket,packet *onepacket){

    //printf("raw packet %s\n",rawPacket);

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

    //printf("next packet version %i type %i\n",onepacket->version,onepacket->type);

    int i=6;
    switch(onepacket->type){
        case 4:{
                   //printf("litteral\n");
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
                     //printf("operator %i version %i\n",onepacket->type, onepacket->version);
                     //operator packet
                     char lengthType = rawPacket[i];
                     i=i+1;
                     //printf("sub packet type %c\n",lengthType);
                     if(lengthType=='0'){
                         //next 15 bits represent the 
                         //number of bits for sub packets
                         char subPacketLengthBits[16];
			 strncpy(subPacketLengthBits,rawPacket+i,15);
			 i+=15;
                         //printf("%s\n%",subPacketLengthBits);
                         int subPacketLength=bitsToInt(subPacketLengthBits);
                         //printf("sub packet length %s %i\n",subPacketLengthBits,subPacketLength);
                         char *bitsarray = malloc(sizeof(char)*(subPacketLength+1));
                         strncpy(bitsarray,rawPacket+i,subPacketLength);
                         onepacket->subPackets=malloc(sizeof(packet)*10);
                         onepacket->subPacketCount = 
                             decodeSubPackets(bitsarray,
                                     onepacket->subPackets);
			 //printf("count %i length %i\n",onepacket->subPacketCount,subPacketLength);
                         i+=subPacketLength;

                     }
                     else { //lengthType=1
                         //next 11 bits represent the number of
                         //sub packes contained in this packet
                         char subPacketCountBits[12];
                         for(int j=0;j<11;j++){
                             subPacketCountBits[j]=rawPacket[i];
                             i++;
                         }
                         subPacketCountBits[11]='\0';
                         int subPacketCount=bitsToInt(subPacketCountBits);
                         //printf("sub packet count %s %i\n",subPacketCountBits,subPacketCount);
                         onepacket->subPacketCount = subPacketCount;
                         onepacket->subPackets=malloc(sizeof(packet)*10);
                         //printf("%i %i %s\n",strlen(rawPacket),i,rawPacket+i);
                         i+=decodeNPackets(rawPacket+i,
                                     onepacket->subPackets,onepacket->subPacketCount);
                         //printf("%i %i %s\n",strlen(rawPacket),i,rawPacket+i);
                         //printf("%i\n",onepacket->subPacketCount);
                     }
                 }
    }
    //printf("decode complete\n");
    return i;
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

   packet packets[3000];

   list *input = stringList(argv[1]);
   //printList(input);

   char *bits = hexToBits(input->data[0]);
   //printf("%s\n",bits);

   numPackets += decodePackets(bits,packets);
   //printf("all decoded\n");
   
   //printPackets(packets,numPackets);

   printf("version sum: %i\n",packetVersionSum(packets,numPackets));

   return 0;
}
