#include "common.h"

typedef struct __digit{
    char pattern[8];
    int length;
    int byte;
    int value;
} digit;

int calculateByte(char *current){
    int retval = 0;
    for(int i=0;i<strlen(current);i++){
        switch(current[i]){
            case 'a': retval = retval | 0x01;
                      break;
            case 'b': retval = retval | 0x02;
                      break;
            case 'c': retval = retval | 0x04;
                      break;
            case 'd': retval = retval | 0x08;
                      break;
            case 'e': retval = retval | 0x10;
                      break;
            case 'f': retval = retval | 0x20;
                      break;
            case 'g': retval = retval | 0x40;
                      break;
        }
    }
    return retval;
}

char getByte(int searchValue,digit digits[10]){
    for(int i=0;i<10;i++){
        if(digits[i].value==searchValue){
            return digits[i].byte;
        }
    }
    return 0;
}

void findMissingValues(digit digits[10]){
    char onebyte = getByte(1,digits);
    char fourbyte = getByte(4,digits);
    char sevenbyte = getByte(7,digits);
    char eightbyte = getByte(8,digits);

    for(int i=0;i<10;i++){
        //printDigits(digits);
        if(digits[i].value==-1){
            //printf("unknown %s\n",digits[i].pattern);
            if(digits[i].length == 5){
               if((digits[i].byte&onebyte)==onebyte){
                   // 3
                   digits[i].value=3;
               } else {
                   // 2 or 5
                   if((digits[i].byte|fourbyte)==eightbyte){
                       digits[i].value=2;
                   } else {
                       digits[i].value=5;
                   }
               }


            } else {
                //digits[i].length == 6;
                if((digits[i].byte|sevenbyte)==eightbyte){
                    // 6
                    digits[i].value=6;
                } else {
                    // 0 or 9
                    if((digits[i].byte|fourbyte)==eightbyte){
                        // 0
                        digits[i].value=0;
                    } else {
                        // must be 9
                        digits[i].value=9;
                    }
                }
            }
        }
    }

}

int getValueForInput(char *input,digit digits[10]){
    char byteval = calculateByte(input);

    for(int i=0;i<10;i++){
        if(byteval==digits[i].byte) return digits[i].value;
    }
    return 0;
}

void printDigits(digit digits[10]){
  for(int i=0;i<10;i++){
      printf("%s: %i\n",digits[i].pattern,digits[i].value);
  }
}


int main(int argc,char **argv){

   list *input = stringList(argv[1]);
   //printList(input);

   int total;

   for(int i=0;i<input->size;i++){
       char *current = strtok(input->data[i]," ");
       digit digits[10];
       int count = 0;
       
       do {
           switch(strlen(current)){
               case 7:{
                  //printf("%s: 8\n",current);
                  strcpy(digits[count].pattern,current);
                  digits[count].value=8;
                  digits[count].byte=calculateByte(current);
                  digits[count].length=7;
                  break;
                      }
               case 4:{
                  //printf("%s: 4\n",current);
                  strcpy(digits[count].pattern,current);
                  digits[count].value=4;
                  digits[count].byte=calculateByte(current);
                  digits[count].length=4;  
                  break;
                      }
               case 3:{
                  //printf("%s: 7\n",current);
                  strcpy(digits[count].pattern,current);
                  digits[count].value=7;
                  digits[count].byte=calculateByte(current);
                  digits[count].length=3;  
                  break;
                      }
               case 2:{
                  //printf("%s: 1\n",current);
                  strcpy(digits[count].pattern,current);
                  digits[count].value=1;
                  digits[count].byte=calculateByte(current);
                  digits[count].length=2;  
                  break;
                      }
               case 6:{
                  //printf("%s: 0,6,9\n",current);
                  strcpy(digits[count].pattern,current);
                  digits[count].value=-1;
                  digits[count].byte=calculateByte(current);
                  digits[count].length=6;  
                  break;
                      }
               case 5:{
                  //printf("%s: 2,3,5\n",current);
                  strcpy(digits[count].pattern,current);
                  digits[count].value=-1;
                  digits[count].byte=calculateByte(current);
                  digits[count].length=5;  
                  break;
                      }
               default:
           }
           count++; 
           current = strtok(NULL," ");
       } while(strcmp(current,"|")!=0);

       findMissingValues(digits);

       current = strtok(NULL," ");
       int subtotal=0;
       do {
         subtotal=subtotal*10;
         subtotal+=getValueForInput(current,digits);
         current = strtok(NULL," ");
       } while( current!=NULL);
       total += subtotal;
   }

   printf("total %i\n",total);

   return 0;
}
