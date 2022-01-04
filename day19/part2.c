// due to errors we know 13136 is too low, 13721 is too high
#include "common.h"
#include "point.h"

#define TRANSFORMS 48

typedef struct __map {
    int scannerNumber;
    int mergedInto;
    point3d scannerPosition;
    int probeCount;
    point3d probePositions[1000];
    transform rotation;
    point3d shift;
} probemap;

transform getIdentityTransform(){
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

    return makeTransformFromColumnVectors(eye1,eye2,eye3);
}

int buildScannerMapsFromInput(list *input,probemap *scannerMaps){
    int currentScannerNo = 0;
    int lastScannerNo=0;
    int numScanners=0; 
    for(int i=0;i<input->size;i++){
        if(sscanf(input->data[i]," --- scanner %i ---",&currentScannerNo)==1){
          lastScannerNo=currentScannerNo;
          scannerMaps[currentScannerNo].scannerNumber=currentScannerNo;
          scannerMaps[currentScannerNo].mergedInto=-1;
          scannerMaps[currentScannerNo].probeCount=0;
          scannerMaps[currentScannerNo].rotation=getIdentityTransform();
          scannerMaps[currentScannerNo].scannerPosition.x=0;
          scannerMaps[currentScannerNo].scannerPosition.y=0;
          scannerMaps[currentScannerNo].scannerPosition.z=0;
          scannerMaps[currentScannerNo].shift.x=0;
          scannerMaps[currentScannerNo].shift.y=0;
          scannerMaps[currentScannerNo].shift.z=0;
          numScanners++;
        } else {
          sscanf(input->data[i]," %i,%i,%i",
                  &scannerMaps[lastScannerNo].probePositions[scannerMaps[lastScannerNo].probeCount].x,
                  &scannerMaps[lastScannerNo].probePositions[scannerMaps[lastScannerNo].probeCount].y,
                  &scannerMaps[lastScannerNo].probePositions[scannerMaps[lastScannerNo].probeCount].z);
          scannerMaps[lastScannerNo].probeCount++;
        }
    }

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

    //printf("%s\n",toString(negativeeye3));

    transform *retval=malloc(sizeof(transform)*TRANSFORMS);
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
    rotatedMap.scannerPosition=calculateTransform(input.scannerPosition,transformMatrix);
    rotatedMap.probeCount=input.probeCount;
    rotatedMap.rotation=transformMatrix;
    rotatedMap.shift=calculateTransform(input.shift,transformMatrix);
    for(int i=0;i<rotatedMap.probeCount;i++){
        rotatedMap.probePositions[i]=calculateTransform(input.probePositions[i],transformMatrix);
    }
    return rotatedMap;
}

probemap shiftMap(probemap input,point3d shift){
    probemap shiftedMap;
    shiftedMap.scannerNumber=input.scannerNumber;
    shiftedMap.scannerPosition=addpoints(input.scannerPosition,shift);
    shiftedMap.shift=shift;
    shiftedMap.rotation=input.rotation;
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
            //printf("map %i contains %s\n",input.scannerNumber,toString(probe));
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

    for(int i=0;i<TRANSFORMS;i++){
       probemap rotated = rotateMap(target,transforms[i]);
       for(int j=0;j<reference.probeCount;j++){
           for(int k=0;k<rotated.probeCount;k++){
              //printf("%s\n",toString(rotated.probePositions[k]));
              point3d shift=subtractpoints(reference.probePositions[j],rotated.probePositions[k]);
              probemap shifted = shiftMap(rotated,shift);
              if(is12PointMatch(reference,shifted)!=0){
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
    //printf("points in merged map %i\n",input.probeCount);
    //printf("points in tomerge map %i\n",tomerge.probeCount);
    return input;
}

void printStatistics(int scannerCount,probemap *scannerMaps){
   for(int i=0;i<scannerCount;i++){
       printf("scanner %i position %s merged into %i count %i\n",
               scannerMaps[i].scannerNumber,
               toString(scannerMaps[i].scannerPosition),
               scannerMaps[i].mergedInto,
               scannerMaps[i].probeCount);
   }

   printf("points in map zero: %i\n",scannerMaps[0].probeCount);
}

void findMaxDistance(int scannerCount,probemap *scannerMaps){
   long maxdist=0;
   for(int i=0;i<scannerCount;i++){
      for(int j=0;j<scannerCount;j++){
          maxdist=max(maxdist,distance(scannerMaps[i].scannerPosition,scannerMaps[j].scannerPosition));
          /*printf("Distance between %i (%s) and %i (%s)= %i\n",
                  i,toString(scannerMaps[i].scannerPosition),j,toString(scannerMaps[j].scannerPosition),distance(scannerMaps[i].scannerPosition,scannerMaps[j].scannerPosition));*/
      }
   }

   printf("max distance %i\n",maxdist);
}

void updateChildMaps(int parent,int scannerCount,probemap *scannerMaps){
     for(int k=0;k<scannerCount;k++){
        if(parent==k) continue;
        if(scannerMaps[k].mergedInto==scannerMaps[parent].scannerNumber){
           scannerMaps[k]=shiftMap(
              rotateMap(scannerMaps[k],scannerMaps[parent].rotation),
              scannerMaps[parent].shift);
           scannerMaps[k].mergedInto=scannerMaps[parent].scannerNumber;
        }
     }
}

void mergeAllMaps(int scannerCount,probemap *scannerMaps){
   int mergedone=0;

   do {
       printf("new pass\n");
       mergedone=0;
       for(int j=0;j<scannerCount;j++){
          for(int i=scannerCount-1;i>=0;i--){
          if(i==j) continue;
          if(scannerMaps[i].mergedInto!=-1) continue;
          if(scannerMaps[j].mergedInto!=-1) continue;
          probemap match = findMapMatch(scannerMaps[j],scannerMaps[i]);
          if(is12PointMatch(scannerMaps[j],match)) {
              printf("matched %i %i\n",j,i);
              scannerMaps[i]=match;
              scannerMaps[i].mergedInto=scannerMaps[j].scannerNumber;
              scannerMaps[j]=mergemaps(scannerMaps[j],match);
              //printmap(scannerMaps[i]);
              //updateChildMaps(i,scannerCount,scannerMaps);
              mergedone=1;
          }
       }
     }
   } while(mergedone==1);
}

int main(int argc,char **argv){

   probemap scannerMaps[40];

   list *input = stringList(argv[1]);
   //printList(input);
   int scannerCount = buildScannerMapsFromInput(input,scannerMaps);
   printf("scanners read %i\n",scannerCount);

   mergeAllMaps(scannerCount,scannerMaps);
   mergeAllMaps(scannerCount,scannerMaps);
   printStatistics(scannerCount,scannerMaps);

   findMaxDistance(scannerCount,scannerMaps);

   return 0;
}
