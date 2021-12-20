#include "common.h"
#include "point.h"

typedef struct __map {
    int sensorNumber;
    point3d sensorPosition;
    int probeCount;
    point3d probePositions[100];
} probemap;

void buildSensorMapsFromInput(list *input,probemap *sensorMaps){
    int currentSensorNo = 0;
    int lastSensorNo=0;
    int probeCount = 0;
    for(int i=0;i<input->size;i++){
        if(sscanf(input->data[i]," --- scanner %i ---",&currentSensorNo)==1){
          sensorMaps[lastSensorNo].probeCount=probeCount;
          lastSensorNo=currentSensorNo;
          sensorMaps[currentSensorNo].sensorNumber=currentSensorNo;
          probeCount=0;
        } else {
          sscanf(input->data[i]," %i,%i,%i",
                  &sensorMaps[lastSensorNo].probePositions[probeCount].x,
                  &sensorMaps[lastSensorNo].probePositions[probeCount].y,
                  &sensorMaps[lastSensorNo].probePositions[probeCount].z);
          probeCount++;
        }
    }

    sensorMaps[0].sensorPosition.x=0;
    sensorMaps[0].sensorPosition.y=0;
    sensorMaps[0].sensorPosition.z=0;
}

int main(int argc,char **argv){

   probemap sensorMaps[40];

   list *input = stringList(argv[1]);
   printList(input);
   void buildSensorMapsFromInput(input,sensorMaps);

   return 0;
}
