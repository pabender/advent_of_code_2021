#include "common.h"
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define PARTS 100 

typedef struct __alu {
    int registers[4];
    char *input;
    int inputindex;
    list *program;
    int programcounter;
} alu;

void printState(alu *runner){
   printf("w: %i x: %i y: %i z: %i\n",
		   runner->registers[0],runner->registers[1],
		   runner->registers[2],runner->registers[3]);
}

void init(alu *runner,char *input,list *program){
    runner->registers[0]=0;
    runner->registers[1]=0;
    runner->registers[2]=0;
    runner->registers[3]=0;
    runner->input=input;
    runner->inputindex=0;
    runner->program=program;
    runner->programcounter=0;
}

void inp(alu *runner,int reg1){
	runner->registers[reg1]=runner->input[runner->inputindex]-'0';
	runner->inputindex++;
}

void mul(alu *runner,int reg1,int reg2,int value){
	if(reg2!=-1){
	   runner->registers[reg1]=runner->registers[reg1]*runner->registers[reg2];
	} else {
	   runner->registers[reg1]=runner->registers[reg1]*value;
	}
}

void add(alu *runner,int reg1,int reg2,int value){
	if(reg2!=-1){
	   runner->registers[reg1]=runner->registers[reg1]+runner->registers[reg2];
	} else {
	   runner->registers[reg1]=runner->registers[reg1]+value;
	}
}

void divide(alu *runner,int reg1,int reg2,int value){
	if(reg2!=-1){
	   runner->registers[reg1]=runner->registers[reg1]/runner->registers[reg2];
	} else {
	   runner->registers[reg1]=runner->registers[reg1]/value;
	}
}

void mod(alu *runner,int reg1,int reg2,int value){
	if(reg2!=-1){
	   runner->registers[reg1]=runner->registers[reg1]%runner->registers[reg2];
	} else {
	   runner->registers[reg1]=runner->registers[reg1]%value;
	}
}

void eql(alu *runner,int reg1,int reg2,int value){
	if(reg2!=-1){
	   runner->registers[reg1]=(runner->registers[reg1]==runner->registers[reg2])?1:0;
	} else {
	   runner->registers[reg1]=(runner->registers[reg1]==value)?1:0;
	}
}


void runProg(alu *runner){
    do {
      char instruction[4];
      char reg1;
      char reg2[10];
      //printf("%s\n",runner->program->data[runner->programcounter]);
      int conversions = sscanf(runner->program->data[runner->programcounter],"%[^ ] %c %[^ ]",
		      instruction,&reg1,reg2);
      int reg1no=reg1-'w';
      int reg2no=-1;
      int value=0;
      if(conversions==3){
         if(isalpha(reg2[0])){
	    reg2no=reg2[0]-'w';
         } else {
            reg2no=-1;
	    value=atoi(reg2);
         }
	 //printf("%s %i %i %i\n",instruction,reg1no,reg2no,value);
         if(strcmp(instruction,"mul")==0){
            mul(runner,reg1no,reg2no,value);
	 } else if(strcmp(instruction,"eql")==0){
            eql(runner,reg1no,reg2no,value);
	 } else if(strcmp(instruction,"add")==0){
            add(runner,reg1no,reg2no,value);
	 } else if(strcmp(instruction,"div")==0){
            divide(runner,reg1no,reg2no,value);
	 } else if(strcmp(instruction,"mod")==0){
            mod(runner,reg1no,reg2no,value);
	 }

      } else {
	inp(runner,reg1no);
      }

      //printState(runner);
      runner->programcounter++;
    }while(runner->programcounter<runner->program->size);
}

long power(int base,int power){
    long result=1;
    for(int i=power;i>0;i--){
	result = result * base;
    }
    return result;
}

void findValidModelNumber(list *input,long floor,long ceiling){
      alu *runner=malloc(sizeof(alu));  
      for(long valid=ceiling;valid>floor;valid--){
         char validation[15];
         sprintf(validation,"%014li",valid);
         if(strstr(validation,"0")!=NULL) {
	      continue;
         }
         //printf("validating %s\n",validation);
         init(runner,validation,input);
         runProg(runner);
         //printState(runner);
         if(runner->registers[3]==0) {
              printf("good %s\n",validation);
	      break;
        }
      }
}

int main(int argc,char **argv){

   list *input = stringList(argv[1]);
   //printList(input);

   //long ceiling=99999999999999;
   long ceiling=13579246899999;
   //long floor=10000000000000;
   //long floor=11932792943189;
   long floor=12821698949199;
   // answer for part 1: 12934998949199

   long quarter=(ceiling-floor)/PARTS;
   pid_t child;

   for(int p=0;p<PARTS;p++){
      if((child = fork())==0){
         ceiling=floor+quarter;
         findValidModelNumber(input,floor,ceiling);
	 break;
      }
      floor=floor+quarter;	     
   }

   int status;
   while(wait(&status)!=0); 

   return 0;
}
