#include "common.h"

int ***makeEmptyBoards(int count){
    int ***boards = malloc(sizeof(int**)*(count));
    for(int board =0;board<count;board++){
        boards[board]=malloc(sizeof(int*)*5);
        for(int row=0;row<5;row++){
            boards[board][row]=malloc(sizeof(int)*5);
            for(int column=0;column<5;column++){
                boards[board][row][column] = 0;
            }
        }
    }
    return boards;
}

int ***makeBoards(list input){
    int ***boards = makeEmptyBoards(input.size/5);
    int inputLine=1;
    for(int board=0;board<input.size/5;board++){
        for(int row = 0;row<5;row++) {
          char *nextInt = strtok(input.data[inputLine++]," ");
          for(int column =0; column<5;column++) {
             boards[board][row][column] = atoi(nextInt);
             nextInt = strtok(NULL," ");
          }
        }
    }
    return boards;
}

void markBoards(int choice,int ***boards,int boardCount){
    for(int board =0;board<boardCount;board++){
        for(int row=0;row<5;row++){
            for(int column=0;column<5;column++){
                if(boards[board][row][column] == choice){
                   boards[board][row][column] = -1; 
                }
            }
        }
    }
}

int calculateScore(int **board){
    int score = 0;
    for(int row=0;row<5;row++){
       for(int column=0;column<5;column++){
          if(board[row][column] != -1){
            score += board[row][column]; 
          }
        }
    }
    return score;
}

int isBoardRowWinner(int **board){
        for(int row=0;row<5;row++){
            if( board[row][0]==-1 &&
                board[row][1]==-1 &&
                board[row][2]==-1 &&
                board[row][3]==-1 &&
                board[row][4]==-1 ) {
                return 0;
            }
        }
        return -1;
}

int isBoardColumnWinner(int **board){
        for(int column=0;column<5;column++){
            if( board[0][column]==-1 &&
                board[1][column]==-1 &&
                board[2][column]==-1 &&
                board[3][column]==-1 &&
                board[4][column]==-1 ) {
                return 0;
            }
        }
        return -1;
}

int checkForWinner(int ***boards,int boardCount){
    for(int board =0;board<boardCount;board++){
        if(isBoardRowWinner(boards[board]) != -1 || isBoardColumnWinner(boards[board]) != -1){
                return calculateScore(boards[board]);
        }
    }
    return -1;
}


int main(int argc,char **argv){

   list *input = stringList(argv[1]);
   //printList(input);

   char *choiceList = input->data[0];

   printf("boards %i\n",(input->size)/5);

   int ***boards = makeBoards(*input);

   printf("boards made\n");

   int winner = -1;
   
   char *choice = strtok(choiceList,",");
   while(choice!=NULL && winner == -1){
       //printf("%s\n",choice);
       markBoards(atoi(choice),boards,(input->size)/5);
       winner = checkForWinner(boards,(input->size)/5);
       if(winner != -1) break;
       choice = strtok(NULL,",");
   }

   if(choice!=NULL) {
      printf("winner %i choice %s score %i\n",winner,choice,winner *atoi(choice));
   }

   return 0;
}
