#ifndef __POINT_H
#define __POINT_H

typedef struct __3dPoint {
    int x;
    int y;
    int z;
} point3d;

point3d addpoints(point3d from ,point3d amount);
point3d subtractpoints(point3d from,point3d amount);
point3d makePoint(int x,int y,int z);
point3d fromString(char *input);
char *toString(point3d point);

#endif
