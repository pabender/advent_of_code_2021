#include "common.h"

int main(int argc,char **argv){

    FILE *f = fopen(argv[1],"r");
    char bits[10000];
    int oneCounts[10000];
    int rows=0;
    long gamma=0;
    long epsilon=0;
    int bitlength=5;

    fscanf(f,"%s",&bits);
    bitlength=strlen(bits);

    do {
        //printf("bits %s\n",bits);
        rows++;
        for(int i=0;i<bitlength;i++){
            if(bits[i]=='1') oneCounts[i]++;
        }
        fscanf(f,"%s",&bits);
    } while(!feof(f));

    fclose(f);

    for(int i=0;i<bitlength;i++){
        printf("bit %i one count %i zero count %i\n",
                bitlength-1-i,
                oneCounts[i],
                rows - oneCounts[i]);

        if(oneCounts[i]>(rows-oneCounts[i])){
          gamma |= (0x01<<((bitlength-1)-i));
        } else {
          epsilon |= (0x01<<((bitlength-1)-i));
        }
    }

    printf( "gamma %i, epsilon %i, product %i\n",
            gamma,epsilon,gamma*epsilon);
   return 0;
}
