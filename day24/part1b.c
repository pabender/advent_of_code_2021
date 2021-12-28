#include "common.h"
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define PARTS 100

typedef struct __alu {
    char registers[4][15000];
    char *input;
    int inputindex;
    list *program;
    int programcounter;
} alu;

void printState(alu *runner){
   printf("w: %s\n x: %s\n y: %s\ z: %s\n",
		   runner->registers[0],runner->registers[1],
		   runner->registers[2],runner->registers[3]);
}

void init(alu *runner,char *input,list *program){
    runner->registers[0][0]='\0';
    runner->registers[1][0]='\0';
    runner->registers[2][0]='\0';
    runner->registers[3][0]='\0';
    runner->input=input;
    runner->inputindex=0;
    runner->program=program;
    runner->programcounter=0;
}

void inp(alu *runner,int reg1){
	runner->registers[reg1][0]=runner->input[runner->inputindex];
	runner->registers[reg1][1]='\0';
	runner->inputindex++;
}

void mul(alu *runner,int reg1,int reg2,int value){
	if(strlen(runner->registers[reg1])>0){
	   strcat(runner->registers[reg1],"*");
	   if(reg2!=-1){
	      strcat(runner->registers[reg1],runner->registers[reg2]);
	   } else {
	      char valueString[10];
	      sprintf(valueString,"%i",value);
	      strcat(runner->registers[reg1],valueString);
	   }
	}
}

void add(alu *runner,int reg1,int reg2,int value){
	if(strlen(runner->registers[reg1])>0){
	   strcat(runner->registers[reg1],"+");
	}
	if(reg2!=-1){
	   strcat(runner->registers[reg1],runner->registers[reg2]);
	} else {
	   char valueString[10];
	   sprintf(valueString,"%i",value);
	   strcat(runner->registers[reg1],valueString);
	}
}

void divide(alu *runner,int reg1,int reg2,int value){
	if(strlen(runner->registers[reg1])>0){
	   strcat(runner->registers[reg1],"/");
	   if(reg2!=-1){
	      strcat(runner->registers[reg1],runner->registers[reg2]);
	   } else {
	      char valueString[10];
	      sprintf(valueString,"%i",value);
	      strcat(runner->registers[reg1],valueString);
	   }
	}
}

void mod(alu *runner,int reg1,int reg2,int value){
	if(strlen(runner->registers[reg1])>0){
	   strcat(runner->registers[reg1],"%");
	   if(reg2!=-1){
	      strcat(runner->registers[reg1],runner->registers[reg2]);
	   } else {
	      char valueString[10];
	      sprintf(valueString,"%i",value);
	      strcat(runner->registers[reg1],valueString);
	   }
	}
}

void eql(alu *runner,int reg1,int reg2,int value){
	if(strlen(runner->registers[reg1])>0){
	   strcat(runner->registers[reg1],"+");
	   if(reg2!=-1){
	      strcat(runner->registers[reg1],runner->registers[reg2]);
	   } else {
	      char valueString[10];
	      sprintf(valueString,"%i",value);
	      strcat(runner->registers[reg1],valueString);
	   }
	}
}


void runProg(alu *runner){
    do {
      char instruction[4];
      char reg1;
      char reg2[10];
      printf("%s\n",runner->program->data[runner->programcounter]);
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

      printState(runner);
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

int main(int argc,char **argv){

   list *input = stringList(argv[1]);
   //printList(input);

   /*long cieling=13579246899999;
   long floor=10000000000000;

   long quarter=(cieling-floor)/PARTS;
   pid_t child;

   for(int p=0;p<PARTS;p++){
      if((child = fork())==0){
         cieling=floor+quarter;
	 break;
      }
      floor=floor+quarter;	     
   }

   if(child==0) {*/
      alu *runner=malloc(sizeof(alu));  
      //for(long valid=cieling;valid>floor;valid--){
         char validation[26];
      /*   sprintf(validation,"%014li",valid);
         if(strstr(validation,"0")!=NULL) {
	      continue;
         }*/
         //printf("validating %s\n",validation);
         init(runner,"ABCDEFGHIJKLMNOP",input);
         runProg(runner);
         //printState(runner);
         /*if(runner->registers[3]==0) {
              printf("valid!!!! %s\n",validation);
	      break;
        }*/
      //}
   /*}

   int status;
   while(wait(&status)!=0); */

   return 0;
}
