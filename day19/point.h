#ifndef __POINT_H
#define __POINT_H

typedef struct __3dPoint {
    long x;
    long y;
    long z;
} point3d;

typedef struct __3by3Matrix {
    long a11;
    long a12;
    long a13;
    long a21;
    long a22;
    long a23;
    long a31;
    long a32;
    long a33;
} transform;

typedef point3d vector;

point3d addpoints(point3d from ,point3d amount);
point3d subtractpoints(point3d from,point3d amount);
point3d makePoint(long x,long y,long z);
point3d fromString(char *input);
char *toString(point3d point);

transform makeTransform(long a11,long a12,long a13,long a21,long a22,long a23,long a31,long a32,long a33);
transform makeTransformFromColumnVectors(vector col1,vector col2,vector col3);
point3d calculateTransform(point3d original,transform transformMatrix);
vector vectorScalerMultiplication(vector v,long i);
long equals(point3d point1,point3d point2);
long distance(point3d point1,point3d point2);

#endif
