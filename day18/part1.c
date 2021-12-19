#include "common.h"

typedef struct pair {
    int value;
    struct pair *left;
    struct pair *right;
} snailfish;

snailfish *addition(snailfish *input1,snailfish *input2){
    snailfish *retval = malloc(sizeof(snailfish));
    retval->left=input1;
    retval->right=input2;
    return retval;
}

int isLeaf(snailfish *input){
    return (input->left==NULL && input->right==NULL);
}

snailfish *split(snailfish *input){
    if(isLeaf(input) && input->value>=10){
        snailfish *retval = malloc(sizeof(snailfish));
        retval->left = malloc(sizeof(snailfish));
        retval->left->value=(input->value/2);
        retval->left->left=NULL;
        retval->left->right=NULL;
        retval->right = malloc(sizeof(snailfish));
        retval->right->value= (input->value/2) + (input->value%2);
        retval->right->left=NULL;
        retval->right->right=NULL;
        return retval;
    }
    return input;
}

int magnitude(snailfish input){
    if(isLeaf(&input)){
        return input.value;
    }
    return 3*magnitude(*input.left) + 2*magnitude(*input.right);
}

void magnitudeTest(){
   snailfish *fishy= malloc(sizeof(snailfish));
   fishy->left=malloc(sizeof(snailfish));
   fishy->left->value=9;
   fishy->left->left=NULL;
   fishy->left->right=NULL;
   fishy->right=malloc(sizeof(snailfish));
   fishy->right->value=1;
   fishy->right->left=NULL;
   fishy->right->right=NULL;

   printf("magnitude %i\n",magnitude(*fishy));

   snailfish *fishy2= malloc(sizeof(snailfish));
   fishy2->left=malloc(sizeof(snailfish));
   fishy2->left->left=malloc(sizeof(snailfish));
   fishy2->left->right=malloc(sizeof(snailfish));
   fishy2->left->left->value=9;
   fishy2->left->left->left=NULL;
   fishy2->left->left->right=NULL;
   fishy2->left->right->value=1;
   fishy2->left->right->left=NULL;
   fishy2->left->right->right=NULL;
   fishy2->right=malloc(sizeof(snailfish));
   fishy2->right->left=malloc(sizeof(snailfish));
   fishy2->right->left->value=1;
   fishy2->right->left->left=NULL;
   fishy2->right->left->right=NULL;
   fishy2->right->right=malloc(sizeof(snailfish));
   fishy2->right->right->value=9;
   fishy2->right->right->left=NULL;
   fishy2->right->right->right=NULL;

   printf("magnitude2 %i\n",magnitude(*fishy2));
}

char *toString(snailfish fish){
   char *buffer=malloc(sizeof(char)*1000);
   char *position=buffer;

    if(isLeaf(&fish)){
        sprintf(buffer,"%i",fish.value);
    } else {
        char *leftBuffer = toString(*fish.left);
        char *rightBuffer = toString(*fish.right);
        sprintf(buffer,"[%s,%s]",leftBuffer,rightBuffer);
        //free(leftBuffer);
        //free(rightBuffer);
    }
   return buffer;
}

void stringTest(){
   snailfish *fishy= malloc(sizeof(snailfish));
   fishy->left=malloc(sizeof(snailfish));
   fishy->left->value=9;
   fishy->left->left=NULL;
   fishy->left->right=NULL;
   fishy->right=malloc(sizeof(snailfish));
   fishy->right->value=1;
   fishy->right->left=NULL;
   fishy->right->right=NULL;

   printf("%s\n",toString(*fishy));

   snailfish *fishy2= malloc(sizeof(snailfish));
   fishy2->left=malloc(sizeof(snailfish));
   fishy2->left->left=malloc(sizeof(snailfish));
   fishy2->left->right=malloc(sizeof(snailfish));
   fishy2->left->left->value=9;
   fishy2->left->left->left=NULL;
   fishy2->left->left->right=NULL;
   fishy2->left->right->value=1;
   fishy2->left->right->left=NULL;
   fishy2->left->right->right=NULL;
   fishy2->right=malloc(sizeof(snailfish));
   fishy2->right->left=malloc(sizeof(snailfish));
   fishy2->right->left->value=1;
   fishy2->right->left->left=NULL;
   fishy2->right->left->right=NULL;
   fishy2->right->right=malloc(sizeof(snailfish));
   fishy2->right->right->value=9;
   fishy2->right->right->left=NULL;
   fishy2->right->right->right=NULL;

   printf("%s\n",toString(*fishy2));
}

char *fromString(char *inputString,snailfish *fish){
    if(inputString[0]=='['){
        fish->left = malloc(sizeof(snailfish));
        char *nextString=fromString(inputString+1,fish->left);
        fish->right= malloc(sizeof(snailfish));
        nextString=fromString(nextString+1,fish->right);
        return nextString+1;
    } else {
        // must be a digit
        fish->value=inputString[0]-'0';
        fish->left=NULL;
        fish->right=NULL;
        return inputString+1;
    }
}

void splitTest(){
   for(int i=0;i<15;i++){   
      snailfish *fishy= malloc(sizeof(snailfish));
      fishy->left=malloc(sizeof(snailfish));
      fishy->value=i;
      fishy->left=NULL;
      fishy->right=NULL;

      snailfish *splitfishy=split(fishy);

      printf("split %s = %s\n",toString(*fishy),toString(*splitfishy));
   }
}

int traverseForSplit(snailfish *input){
    int retval=0;
    if(isLeaf(input->left) && input->left->value>=10){
        input->left=split(input->left);
        printf("split\n");
        return 1;
    } else if(!isLeaf(input->left)){
        retval = traverseForSplit(input->left);
    }
    if(retval!=0){
       if(isLeaf(input->right) && input->right->value>=10){
           input->right=split(input->right);
           printf("split\n");
           return 1;
       } else if(!isLeaf(input->right)){
           retval = traverseForSplit(input->right);
       }
    }
    return retval;
}

int addToRightRegularNumber(snailfish *start,int value){
    if(isLeaf(start)){
       start->value+=value;
       return 1;
    } 
    if(addToRightRegularNumber(start->left,value)!=0){
       return 1;
    }
    if(addToRightRegularNumber(start->right,value)!=0){
       return 1;
    }
    return 0;
}

int addToLeftRegularNumber(snailfish *start,int value){
    if(isLeaf(start)){
       start->value+=value;
       return 1;
    } 
    if(addToLeftRegularNumber(start->right,value)!=0){
       return 1;
    }
    if(addToLeftRegularNumber(start->left,value)!=0){
       return 1;
    }
    return 0;
}

snailfish *lastLeaf = NULL;
snailfish *valueToExplode = NULL;
snailfish *nextLeaf = NULL;

int explode(snailfish *input,int depth){
        int changed=0;
	if(isLeaf(input)){
	   //printf("explod hit leaf\n");
	   if(valueToExplode==NULL) {
	      lastLeaf=input;
	   } else if(nextLeaf==NULL){
	      nextLeaf=input;
	   }
	   return changed;
	}
	if(depth==3){
		if(!isLeaf(input->left)){
		    printf("explode left pair %s\n",toString(*input->left));
		    valueToExplode = input->left;
		    addToRightRegularNumber(input->right,input->left->right->value);
                    if(lastLeaf!=NULL){
		       lastLeaf->value+=input->left->left->value;
		    }
		    input->left->value=0;
		    input->left->left=NULL;
		    input->left->right=NULL;
		    return 1;
		}
		if(!isLeaf(input->right)) {
		    printf("explode right pair %s\n",toString(*input->right));
		    valueToExplode = input->right;
		    input->left->value+=input->right->left->value;
		    input->right->value=0;
		    input->right->left=NULL;
		    input->right->right=NULL;
		    return 1;
		}
	}

	if(changed = explode(input->left,depth+1)==0){
	   changed = explode(input->right,depth+1);
	}
	return changed;
}

snailfish *reduce(snailfish *input){
    int changed =0;
    do {
	lastLeaf=NULL;
        if((changed=explode(input,0))==0){
            changed=traverseForSplit(input);
        }
    } while(changed!=0);
    return input;
}

void explodeTest(){
    snailfish *fishy = malloc(sizeof(snailfish));
    fromString("[[[[[9,8],1],2],3],4]",fishy);
    printf("%s exploded ",toString(*fishy));
    explode(fishy,0);
    printf("%s\n",toString(*fishy));

    fishy = malloc(sizeof(snailfish));
    fromString("[7,[6,[5,[4,[3,2]]]]]",fishy);
    printf("%s exploded ",toString(*fishy));
    explode(fishy,0);
    printf("%s\n",toString(*fishy));

    fishy = malloc(sizeof(snailfish));
    fromString("[[6,[5,[4,[3,2]]]],1]",fishy);
    printf("%s exploded ",toString(*fishy));
    explode(fishy,0);
    printf("%s\n",toString(*fishy));

    fishy = malloc(sizeof(snailfish));
    fromString("[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]",fishy);
    printf("%s exploded ",toString(*fishy));
    explode(fishy,0);
    printf("%s\n",toString(*fishy));
    explode(fishy,0);
    printf("%s\n",toString(*fishy));
    printf("%s exploded ",toString(*fishy));
    explode(fishy,0);
    printf("%s\n",toString(*fishy));
}

int main(int argc,char **argv){

   list *input = stringList(argv[1]);
   //printList(input);

   //stringTest();
   //magnitudeTest();
   //splitTest();
   explodeTest();
   /*snailfish **fishvalues=malloc(sizeof(snailfish *)*input->size);

   for(int i=0;i<input->size;i++){
     fishvalues[i] = malloc(sizeof(snailfish));
     fromString(input->data[i],fishvalues[i]);
     printf("%s magnitude %i\n",toString(*fishvalues[i]),magnitude(*fishvalues[i]));
   }

   snailfish *result=fishvalues[0];
   for(int i=1;i<input->size;i++){
      result=reduce(addition(result,fishvalues[i]));
      printf("%s magnitude %i\n",toString(*result),magnitude(*result));
   }*/

   return 0;
}
