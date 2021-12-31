#include "common.h"
#include "point.h"

typedef struct __map {
    int scannerNumber;
    point3d scannerPosition;
    int probeCount;
    point3d probePositions[1000];
} probemap;

int buildScannerMapsFromInput(list *input,probemap *scannerMaps){
    int currentScannerNo = 0;
    int lastScannerNo=0;
    int probeCount = 0;
    int numScanners=0; 
    for(int i=0;i<input->size;i++){
        if(sscanf(input->data[i]," --- scanner %i ---",&currentScannerNo)==1){
          scannerMaps[lastScannerNo].probeCount=probeCount;
          lastScannerNo=currentScannerNo;
          scannerMaps[currentScannerNo].scannerNumber=currentScannerNo;
          probeCount=0;
          numScanners++;
        } else {
          sscanf(input->data[i]," %i,%i,%i",
                  &scannerMaps[lastScannerNo].probePositions[probeCount].x,
                  &scannerMaps[lastScannerNo].probePositions[probeCount].y,
                  &scannerMaps[lastScannerNo].probePositions[probeCount].z);
          probeCount++;
        }
    }

    scannerMaps[0].scannerPosition.x=0;
    scannerMaps[0].scannerPosition.y=0;
    scannerMaps[0].scannerPosition.z=0;
    return numScanners;
}

transform *getTransformMatricies(){
    vector eye1;
    eye1.x=1;
    eye1.y=0;
    eye1.z=0;
    vector eye2;
    eye2.x=0;
    eye2.y=1;
    eye2.z=0;
    vector eye3;
    eye3.x=0;
    eye3.y=0;
    eye3.z=1;

    vector negativeeye1=vectorScalerMultiplication(eye1,-1);
    vector negativeeye2=vectorScalerMultiplication(eye2,-1);
    vector negativeeye3=vectorScalerMultiplication(eye3,-1);

    transform *retval=malloc(sizeof(transform)*48);
    retval[0]=makeTransformFromColumnVectors(eye1,eye2,eye3);
    retval[1]=makeTransformFromColumnVectors(eye1,eye3,eye2);
    retval[2]=makeTransformFromColumnVectors(eye2,eye1,eye3);
    retval[3]=makeTransformFromColumnVectors(eye2,eye3,eye1);
    retval[4]=makeTransformFromColumnVectors(eye3,eye1,eye2);
    retval[5]=makeTransformFromColumnVectors(eye3,eye2,eye1);
    retval[6]=makeTransformFromColumnVectors(negativeeye1,eye2,eye3);
    retval[7]=makeTransformFromColumnVectors(negativeeye1,eye3,eye2);
    retval[8]=makeTransformFromColumnVectors(eye2,negativeeye1,eye3);
    retval[9]=makeTransformFromColumnVectors(eye2,eye3,negativeeye1);
    retval[10]=makeTransformFromColumnVectors(eye3,negativeeye1,eye2);
    retval[11]=makeTransformFromColumnVectors(eye3,eye2,negativeeye1);
    retval[12]=makeTransformFromColumnVectors(eye1,negativeeye2,eye3);
    retval[13]=makeTransformFromColumnVectors(eye1,eye3,negativeeye2);
    retval[14]=makeTransformFromColumnVectors(negativeeye2,eye1,eye3);
    retval[15]=makeTransformFromColumnVectors(negativeeye2,eye3,eye1);
    retval[16]=makeTransformFromColumnVectors(eye3,eye1,negativeeye2);
    retval[17]=makeTransformFromColumnVectors(eye3,negativeeye2,eye1);
    retval[18]=makeTransformFromColumnVectors(eye1,eye2,negativeeye3);
    retval[19]=makeTransformFromColumnVectors(eye1,negativeeye3,eye2);
    retval[20]=makeTransformFromColumnVectors(eye2,eye1,negativeeye3);
    retval[21]=makeTransformFromColumnVectors(eye2,negativeeye3,eye1);
    retval[22]=makeTransformFromColumnVectors(negativeeye3,eye1,eye2);
    retval[23]=makeTransformFromColumnVectors(negativeeye3,eye2,eye1);
    retval[24]=makeTransformFromColumnVectors(negativeeye1,negativeeye2,eye3);
    retval[25]=makeTransformFromColumnVectors(negativeeye1,eye3,negativeeye2);
    retval[26]=makeTransformFromColumnVectors(negativeeye2,negativeeye1,eye3);
    retval[27]=makeTransformFromColumnVectors(negativeeye2,eye3,negativeeye1);
    retval[28]=makeTransformFromColumnVectors(negativeeye3,negativeeye1,eye2);
    retval[29]=makeTransformFromColumnVectors(eye3,negativeeye2,negativeeye1);
    retval[30]=makeTransformFromColumnVectors(eye1,negativeeye2,negativeeye3);
    retval[31]=makeTransformFromColumnVectors(eye1,negativeeye3,negativeeye2);
    retval[32]=makeTransformFromColumnVectors(negativeeye2,eye1,negativeeye3);
    retval[33]=makeTransformFromColumnVectors(negativeeye2,negativeeye3,eye1);
    retval[34]=makeTransformFromColumnVectors(negativeeye3,eye1,negativeeye2);
    retval[35]=makeTransformFromColumnVectors(negativeeye3,negativeeye2,eye1);
    retval[36]=makeTransformFromColumnVectors(negativeeye1,eye2,negativeeye3);
    retval[37]=makeTransformFromColumnVectors(negativeeye1,negativeeye3,eye2);
    retval[38]=makeTransformFromColumnVectors(eye2,negativeeye1,negativeeye3);
    retval[39]=makeTransformFromColumnVectors(eye2,negativeeye3,negativeeye1);
    retval[40]=makeTransformFromColumnVectors(negativeeye3,negativeeye1,eye2);
    retval[41]=makeTransformFromColumnVectors(negativeeye3,eye2,negativeeye1);
    retval[42]=makeTransformFromColumnVectors(negativeeye1,negativeeye2,negativeeye3);
    retval[43]=makeTransformFromColumnVectors(negativeeye1,negativeeye3,negativeeye2);
    retval[44]=makeTransformFromColumnVectors(negativeeye2,negativeeye1,negativeeye3);
    retval[45]=makeTransformFromColumnVectors(negativeeye2,negativeeye3,negativeeye1);
    retval[46]=makeTransformFromColumnVectors(negativeeye3,negativeeye1,negativeeye2);
    retval[47]=makeTransformFromColumnVectors(negativeeye3,negativeeye2,negativeeye1);
    return retval;
}

probemap rotateMap(probemap input,transform transformMatrix){
    probemap rotatedMap;
    rotatedMap.scannerNumber=input.scannerNumber;
    rotatedMap.scannerPosition=input.scannerPosition;
    rotatedMap.probeCount=input.probeCount;
    for(int i=0;i<rotatedMap.probeCount;i++){
        rotatedMap.probePositions[i]=calculateTransform(input.probePositions[i],transformMatrix);
    }
    return rotatedMap;
}

probemap shiftMap(probemap input,point3d shift){
    probemap shiftedMap;
    shiftedMap.scannerNumber=input.scannerNumber;
    shiftedMap.scannerPosition=input.scannerPosition;
    shiftedMap.probeCount=input.probeCount;
    for(int i=0;i<shiftedMap.probeCount;i++){
        shiftedMap.probePositions[i]=addpoints(input.probePositions[i],shift);
    }
    return shiftedMap;
}

void printmap(probemap input){
    printf("--- scanner %i ---\n",input.scannerNumber);
    printf("probe count %i\n",input.probeCount);
    for(int i=0;i<input.probeCount;i++){
        printf("%s\n",toString(input.probePositions[i]));
    }
}

int mapcontains(probemap input, point3d probe){
    for(int i=0;i<input.probeCount;i++){
        if(equals(input.probePositions[i],probe)){
            return 1;
        }
    }
    return 0;
}

int is12PointMatch(probemap original,probemap shifted){
    int matches=0;
    for(int i=0;i<shifted.probeCount;i++){
        if(mapcontains(original,shifted.probePositions[i])){
           matches++;
        }
    }
    //if(matches >1) printf("matches %i %i: %i\n",original.scannerNumber,shifted.scannerNumber,matches);
    return matches>11;
}

// need a method to try all posible rotations and point shifts 
// to see if we have a match with a given map.
probemap findMapMatch(probemap reference, probemap target){
    transform *transforms=getTransformMatricies();

    for(int i=0;i<48;i++){
       probemap rotated = rotateMap(target,transforms[i]);
       for(int j=0;j<reference.probeCount;j++){
           for(int k=0;k<rotated.probeCount;k++){
              point3d shift=subtractpoints(reference.probePositions[j],rotated.probePositions[k]);
              probemap shifted = shiftMap(rotated,shift);
              if(is12PointMatch(reference,shifted)!=0){
                 shifted.scannerPosition.x=shift.x;
                 shifted.scannerPosition.y=shift.y;
                 shifted.scannerPosition.z=shift.z;
                 return shifted;
              }
           }
       }
    }
    return target;
}

probemap mergemaps(probemap input,probemap tomerge){
    //printf("points in input map %i\n",input.probeCount);
    //printf("points in tomerge map %i\n",tomerge.probeCount);
    for(int i=0;i<tomerge.probeCount;i++){
        if(!mapcontains(input,tomerge.probePositions[i])){
           input.probePositions[input.probeCount]=tomerge.probePositions[i];
           input.probeCount++;
        }
    }
    printf("points in merged map %i\n",input.probeCount);
    //printf("points in tomerge map %i\n",tomerge.probeCount);
    return input;
}


// need a method to combine maps into a single map with a unique set of points.

int main(int argc,char **argv){

   probemap scannerMaps[40];

   list *input = stringList(argv[1]);
   printList(input);
   int scannerCount = buildScannerMapsFromInput(input,scannerMaps);
   printf("scanners read %i\n",scannerCount);

   int mergedone=0;

   do {
       printf("new pass\n");
   mergedone=0;
   for(int j=0;j<scannerCount;j++){
      for(int i=0;i<scannerCount;i++){
       if(i==j) continue;
       //if(scannerMaps[i].scannerPosition.x!=0 || scannerMaps[i].scannerPosition.y!=0 || scannerMaps[i].scannerPosition.z!=0) continue;
       //if(scannerMaps[j].scannerPosition.x!=0 || scannerMaps[j].scannerPosition.y!=0 || scannerMaps[j].scannerPosition.z!=0) continue;
       probemap match = findMapMatch(scannerMaps[j],scannerMaps[i]);
       if(match.scannerPosition.x!=0 || match.scannerPosition.y!=0 || match.scannerPosition.z!=0){
           printf("matched %i %i\n",j,i);
           match.scannerPosition.x=0;
           match.scannerPosition.y=0;
           match.scannerPosition.z=0;
           scannerMaps[i]=match;
           scannerMaps[j]=mergemaps(scannerMaps[j],match);
           //printmap(scannerMaps[i]);
           mergedone=1;
       }
       }
     }
   } while(mergedone==1);

   printf("points in map zero: %i\n",scannerMaps[0].probeCount);

   return 0;
}
