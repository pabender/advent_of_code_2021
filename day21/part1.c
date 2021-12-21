#include "common.h"

int main(int argc,char **argv){

   int player[2];
   int playerscore[]={0,0};
   int value=0;
   int roll=0;
   int turn=0;

   list *input = stringList(argv[1]);
   printList(input);

   sscanf(input->data[0]," Player 1 starting position: %i",&player[0]);
   sscanf(input->data[1]," Player 2 starting position: %i",&player[1]);

   while(playerscore[0]<1000 && playerscore[1]<1000){
       printf("Player %i position %i score %i rolls completed %i\n",turn,player[turn],playerscore[turn],roll);
       value=((value)%100)+1;
       printf("roll 1 %i\n",value);
       player[turn]=player[turn]+value;
       value=((value)%100)+1;
       printf("roll 2 %i\n",value);
       player[turn]=player[turn]+value;
       value=((value)%100)+1;
       printf("roll 3 %i\n",value);
       player[turn]=(player[turn]+value)%10;
       playerscore[turn]+=player[turn]==0?10:player[turn];
       printf("end position %i end score %i\n",player[turn],playerscore[turn]);
       roll+=3;
       turn=(turn+1)%2;
   }

   int winnerscore = max(playerscore[0],playerscore[1]);
   int looserscore = min(playerscore[0],playerscore[1]);

   printf("rolls %i winner %i, looser %i, product rolls*looser %i\n",roll,winnerscore,looserscore,roll*looserscore);
   

   return 0;
}
