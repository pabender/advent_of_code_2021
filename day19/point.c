#include "point.h"

point3d addpoints(point3d from ,point3d amount){
    return makePoint(from.x+amount.x,from.y+amount.y,from.z+amount.z);
}

point3d subtractpoints(point3d from,point3d amount){
    return makePoint(from.x-amount.x,from.y-amount.y,from.z-amount.z);
}

point3d makePoint(int x,int y,int z){
    point3d retval;
    retval.x=x;
    retval.y=y;
    retval.z=z;
    return retval;
}

point3d fromString(char *input){
    point3d retval;
    sscanf(input," %i,%i,%i",&retval.x,&retval.y,&retval.z);
    return retval;
}

char *toString(point3d point){
    char *buffer=malloc(sizeof(char)*100);
    sprintf(buffer,"%i,%i,%i",point.x,point.y,point.z);
    return buffer;
}

