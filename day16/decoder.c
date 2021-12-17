#include "common.h"
#include <limits.h>
#include "decoder.h"

int decodeSubPackets(char *input,packet *packetArray){
    int bitsConsumed=0;
    int numPacketsConsumed=0;
    while(bitsConsumed<strlen(input)){
       //printf("decode packets %i bits %i\n",numPacketsConsumed,bitsConsumed);
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
                         int bitsConsumed=decodeNPackets(rawPacket+i,
                                     onepacket->subPackets,onepacket->subPacketCount);
                         i+=bitsConsumed;
                         //printf("%i %i %s\n",strlen(rawPacket),i,rawPacket+i);
                         //printf("SubPacketCount %i bits %i\n",onepacket->subPacketCount,bitsConsumed);
                     }
                 }
    }
    //printf("decode complete\n");
    return i;
}

int packetVersionSum(packet p){
    int sum=0;
    sum+=p.version;
        if(p.subPacketCount>0){
            for(int i=0;i<p.subPacketCount;i++) {
            sum+=packetVersionSum(p.subPackets[i]);
        }
    }
    return sum;
}

void printPacket(packet p){
    char indent[1000];
    indent[0]='\0';
    printPacketWithIndent(p,indent);
}

void printPacketWithIndent(packet p,char indent[1000]){
    printf("%sPacket version %i type %i subPacketCount %i value %llu\n",
       indent, p.version,p.type,p.subPacketCount,calculate(p));
    if(p.subPacketCount>0){
       printf("%ssubPackets: \n",indent);
       int index=strlen(indent);
       indent[index]=' ';
       indent[index+1]='\0';
       for(int i=0;i<p.subPacketCount;i++) {
          printPacketWithIndent(p.subPackets[i],indent);
       }
       indent[index]='\0';
       printf("%send subPackets: \n",indent);
    }
}

double calculate(packet packetValue){
        switch(packetValue.type){
            case 0: {// sum all sub packets
                        double sum = 0;
                        for(int j=0;j<packetValue.subPacketCount;j++){
                            double nextValue = calculate(packetValue.subPackets[j]);
                            //printf("next value for sum %llu\n",nextValue);
                            sum = sum + nextValue;
                        }
                        //printf("sum %llu\n",sum);
                        return sum;
                    }
                break;
            case 1: {// product of all sub packets
                        double product = 1;
                        for(int j=0;j<packetValue.subPacketCount;j++){
                            double nextValue = calculate(packetValue.subPackets[j]);
                            //printf("next value for product %llu\n",nextValue);
                            product= product * nextValue;
                        }
                        //printf("product %llu\n",product);
                        return product;
                    }
                break;
            case 2: { // minimum of all sub packets
                        double minimum = ULLONG_MAX;
                        for(int j=0;j<packetValue.subPacketCount;j++){
                            minimum = min(minimum,calculate(packetValue.subPackets[j]));
                        }
                        //printf("minimum %llu\n",minimum);
                        return minimum;
                    }
                break;
            case 3: { // maximum of all sub packets
                        double maximum = 0;
                        for(int j=0;j<packetValue.subPacketCount;j++){
                            maximum = max(maximum,calculate(packetValue.subPackets[j]));
                        }
                        //printf("maximum %llu\n",maximum);
                        return maximum;
                    }
                break;
            case 4: // value
                //printf("value %llu\n",bitsToLLU(packetValue.data));
                return bitsToLLU(packetValue.data);
                break;
            case 5: { // greater than return true of first > second
                       double first = calculate(packetValue.subPackets[0]);
                       double second = calculate(packetValue.subPackets[1]);
                       if(first>second){ 
                           //printf("%llu > %llu\n",first,second);
                           return 1;
                       }
                       //printf("!%llu > %llu\n",first,second);
                       return 0;
                    }
                break;
            case 6: { // less than return 1 if first < second
                       double first = calculate(packetValue.subPackets[0]);
                       double second = calculate(packetValue.subPackets[1]);
                       if(first<second) {
                           //printf("%llu < %llu\n",first,second);
                           return 1;
                       }
                       return 0;
                       //printf("!%llu < %llu\n",first,second);
                    }
                break;
            case 7: { // equals retrn 1 if first == second
                       double first = calculate(packetValue.subPackets[0]);
                       double second = calculate(packetValue.subPackets[1]);
                       if(first==second) { 
                           //printf("%llu == %llu\n",first,second);
                           return 1;
                       }
                       //printf("%llu != %llu\n",first,second);

                       return 0;
                    }
                break;
        }
}

