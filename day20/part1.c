#include "common.h"

typedef struct __image{
    int rows;
    int columns;
    char **pixels;
} image;

int itteration=0;

char getPixel(image *input,int row,int column){
    //printf("get pixel %i %i\n",row,column);
    if( row < 0 || 
        column <0 || 
        row>=input->rows || 
        column>=input->columns){
        if(itteration%2==1) {
           return '.';
        } else {
            return '#';
        }
    }
    return input->pixels[row][column];
}

image *getImageFromInput(list *input){
    image *picture = malloc(sizeof(image));
    picture->rows = input->size-1;
    picture->columns = strlen(input->data[1]);
    picture->pixels = malloc(sizeof(char *)*picture->rows);
    for(int i=1;i<=picture->rows;i++){
       picture->pixels[i-1]=malloc(sizeof(char)*(picture->columns+1));
       strcpy(picture->pixels[i-1],input->data[i]);
    } 
    return picture;
}

char *getBitString(image *input,int row,int column){
    char *bitString=malloc(sizeof(char)*10);
    bitString[0]=getPixel(input,row-1,column-1)=='#'?'1':'0';
    bitString[1]=getPixel(input,row-1,column)=='#'?'1':'0';
    bitString[2]=getPixel(input,row-1,column+1)=='#'?'1':'0';
    bitString[3]=getPixel(input,row,column-1)=='#'?'1':'0';
    bitString[4]=getPixel(input,row,column)=='#'?'1':'0';
    bitString[5]=getPixel(input,row,column+1)=='#'?'1':'0';
    bitString[6]=getPixel(input,row+1,column-1)=='#'?'1':'0';
    bitString[7]=getPixel(input,row+1,column)=='#'?'1':'0';
    bitString[8]=getPixel(input,row+1,column+1)=='#'?'1':'0';
    bitString[9]='\0';
    return bitString;
}

image *enhance(image *input,char *enhancementAlgorithm){
    image *output= malloc(sizeof(image));
    output->rows=input->rows+2;
    output->columns=input->columns+2;
    output->pixels=malloc(sizeof(char *)*output->rows);
    for(int row=0;row<output->rows;row++){
       output->pixels[row]=malloc(sizeof(char)*(output->columns+1));
       for(int column=0;column<output->columns;column++){
           //printf("%i %i\n",row,column);
           char *bitString=getBitString(input,row-1,column-1);
           //printf("%s\n",bitString);
           int enhanceindex=bitsToInt(bitString);
           //printf("index %i\n",enhanceindex);
           output->pixels[row][column]=enhancementAlgorithm[enhanceindex];
       }
       output->pixels[row][output->columns]='\0';
    }
    return output;
};

int getLightPixelCount(image *input){
    int count = 0;
    printf("getLightPixelCount %i %i\n",input->rows,input->columns);
    for(int row=0;row<input->rows;row++){
        for(int column=0;column<input->columns;column++){
            if(getPixel(input,row,column)=='#'){
                count++;
            }
        }
    }
    return count;
}

void printImage(image *input){
    for(int row=0;row<input->rows;row++){
        for(int column=0;column<input->columns;column++){
           printf("%c",getPixel(input,row,column));
        }
        printf("\n");
    }
}

int main(int argc,char **argv){

   list *input = stringList(argv[1]);
   //printList(input);

   char *enhancementAlgorithm=input->data[0];

   image *originalImage = getImageFromInput(input);
   printImage(originalImage);
   image *enhancedImage = originalImage; 
   printf("\n");
   printf("light pixel count %i\n",getLightPixelCount(enhancedImage));
   for(int i=0;i<2;i++){
      if(enhancementAlgorithm[0]=='#'){
           itteration=i+1;
      } else {
          itteration=1;
      }
      enhancedImage = enhance(enhancedImage,enhancementAlgorithm);
      printImage(enhancedImage);
      printf("\n");
      printf("light pixel count %i\n",getLightPixelCount(enhancedImage));
   }


   return 0;
}
