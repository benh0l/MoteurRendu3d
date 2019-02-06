//
// Created by Benoît on 27/01/2019.
//

#ifndef MOTEURRENDU3D_POINT_H
#define MOTEURRENDU3D_POINT_H


#include "Matrix.h"

struct Point {
    int x,y,z;
public :
    Point(int x, int y, int z);
    Point();
    int getX();
    int getY();
    int getZ();
    //Matrix point2matrix();
};


#endif //MOTEURRENDU3D_POINT_H
