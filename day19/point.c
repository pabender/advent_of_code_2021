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


transform makeTransform(int a11,int a12,int a13,int a21,int a22,int a23,int a31,int a32,int a33){
    transform retval;
    retval.a11=a11;
    retval.a12=a12;
    retval.a13=a13;
    retval.a21=a21;
    retval.a22=a22;
    retval.a23=a23;
    retval.a31=a31;
    retval.a32=a32;
    retval.a33=a33;
    return retval;
}

transform makeTransformFromColumnVectors(vector col1,vector col2,vector col3){
    transform retval;
    retval.a11=col1.x;
    retval.a12=col2.x;
    retval.a13=col3.x;
    retval.a21=col1.y;
    retval.a22=col2.y;
    retval.a23=col3.y;
    retval.a31=col1.z;
    retval.a32=col2.z;
    retval.a33=col3.z;
    return retval;
}

point3d calculateTransform(point3d original,transform transformMatrix){
    point3d retval;
    retval.x=transformMatrix.a11*original.x
            +transformMatrix.a21*original.y
            +transformMatrix.a31*original.z;

    retval.y=transformMatrix.a12*original.x
            +transformMatrix.a22*original.y
            +transformMatrix.a32*original.z;

    retval.z=transformMatrix.a13*original.x
            +transformMatrix.a23*original.y
            +transformMatrix.a33*original.z;
    return retval;
}

vector vectorScalerMultiplication(vector v,int i){
    vector retval;
    retval.x = v.x*i;
    retval.y = v.y*i;
    retval.z = v.z*i;
}

int equals(point3d point1,point3d point2){
    return point1.x==point2.x && point1.y==point2.y && point1.z==point2.z;
}
