//
// Created by Benoît on 27/01/2019.
//

#include "Vector.h"
#include "Matrix.h"

Vector::Vector(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector::Vector() {

}

float Vector::getX(){
    return this->x;
}

float Vector::getY() {
    return this->y;
}

float Vector::getZ() {
    return this->z;
}

/*
Matrix Vector::vector2matrix() {
    Matrix mat;
    mat.m[0][0] = this->x;
    mat.m[1][0] = this->y;
    mat.m[2][0] = this->z;
    mat.m[3][0] = 1.f;
    return mat;
}*/