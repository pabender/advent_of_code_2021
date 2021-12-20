#ifndef __POINT_H
#define __POINT_H

typedef struct __3dPoint {
    int x;
    int y;
    int z;
} point3d;

typedef struct __3by3Matrix {
    int a11;
    int a12;
    int a13;
    int a21;
    int a22;
    int a23;
    int a31;
    int a32;
    int a33;
} transform;

typedef point3d vector;

point3d addpoints(point3d from ,point3d amount);
point3d subtractpoints(point3d from,point3d amount);
point3d makePoint(int x,int y,int z);
point3d fromString(char *input);
char *toString(point3d point);

transform makeTransform(int a11,int a12,int a13,int a21,int a22,int a23,int a31,int a32,int a33);
transform makeTransformFromColumnVectors(vector col1,vector col2,vector col3);
point3d calculateTransform(point3d original,transform transformMatrix);
vector vectorScalerMultiplication(vector v,int i);

#endif
