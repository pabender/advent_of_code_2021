#include <stdio.h>
#include <stdlib.h>

static int depth=0;
static int horizontalPosition=0;

int getCurrentDepth(){
   return depth;
}

int getCurrentHorizontalPosition(){
   return horizontalPosition;
}

void forward(int move){
   horizontalPosition += move; 
}

void backward(int move){
   horizontalPosition -= move; 
}

void up(int move){
    depth -= move;
}

void down(int move){
    depth += move;
}
