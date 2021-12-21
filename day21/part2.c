#include "common.h"

int stateAddition(int i){
    switch(i){
        case 9:
        case 3: return 1;
                break;
        case 8:
        case 4: return 3;
                break;
        case 7:
        case 5: return 6;
                break;
        case 6: return 7;
                break;
        default: return 0;
    }

}

typedef struct __state{
   int player[2];
   int playerscore[2];
   unsigned long long count;
} state;

unsigned long long *turn(unsigned long long activeStates, state *states,int currentTurn){
    state *newStates = malloc(sizeof(state)*(activeStates*7));
    unsigned long long newActiveStates=0;
    unsigned long long *winners = malloc(sizeof(unsigned long long)*2);
    winners[0]=0;
    winners[1]=0;
    for(int i=0;i<activeStates;i++){
        for(int j=3;j<10;j++){
            state baseState = states[i];
            baseState.player[currentTurn]= (baseState.player[currentTurn]+j)%10;
            baseState.count=states[i].count * stateAddition(j);
            baseState.playerscore[currentTurn]+=baseState.player[currentTurn]==0?10:baseState.player[currentTurn];
            if(baseState.playerscore[currentTurn]>=21){
                winners[currentTurn]+=baseState.count;
            } else {
              newStates[newActiveStates]=baseState;
              newActiveStates++;
            }
        }
    }


    if(newActiveStates>0){
        unsigned long long *childWinners = turn(newActiveStates,newStates,(currentTurn+1)%2);
        winners[0]+= childWinners[0];
        winners[1]+= childWinners[1];
    }
        
    printf("winners 0 %llu 1 %llu active states %llu\n",winners[0],winners[1],activeStates);


    return winners;

}


int main(int argc,char **argv){

   int player[2];

   list *input = stringList(argv[1]);
   printList(input);

   sscanf(input->data[0]," Player 1 starting position: %i",&player[0]);
   sscanf(input->data[1]," Player 2 starting position: %i",&player[1]);

   state states[1];
   states[0].player[0]=player[0];
   states[0].player[1]=player[1];
   states[0].count=1;
   states[0].playerscore[0]=0;
   states[0].playerscore[1]=0;
        

   unsigned long long *winners = turn(1,states,0);
      
   printf("zeros %llu ones %llu\n",winners[0],winners[1]);

   return 0;
}
