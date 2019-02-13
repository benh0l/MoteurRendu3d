//
// Created by Benoît on 27/01/2019.
//

#ifndef MOTEURRENDU3D_VECTOR_H
#define MOTEURRENDU3D_VECTOR_H


#include "Matrix.h"

struct Vector {
    float x, y, z;
public :
    Vector(float x, float y, float z);
    Vector();
    float getX();
    float getY();
    float getZ();
    Vector vectorMinus(Vector v2);
    Vector normalize();
    Vector cross(Vector v2);
    //Matrix vector2matrix();
};


#endif //MOTEURRENDU3D_VECTOR_H
