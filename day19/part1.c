#include "common.h"
#include "point.h"

typedef struct __map {
    int scannerNumber;
    point3d scannerPosition;
    int probeCount;
    point3d probePositions[100];
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

    transform *retval=malloc(sizeof(transform)*24);
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

int main(int argc,char **argv){

   probemap scannerMaps[40];

   list *input = stringList(argv[1]);
   printList(input);
   int scannerCount = buildScannerMapsFromInput(input,scannerMaps);
   printf("scanners read %i\n",scannerCount);

   transform *transforms=getTransformMatricies();

   probemap rotatedmap = rotateMap(scannerMaps[2],transforms[3]);

   printmap(scannerMaps[2]);
   printmap(rotatedmap);


   return 0;
}
