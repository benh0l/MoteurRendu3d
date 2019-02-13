//
// Created by Benoît on 27/01/2019.
//

#include <cmath>
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

Vector Vector::vectorMinus(Vector v2){
    Vector res;
    res.x = this->x - v2.x;
    res.y = this->y - v2.y;
    res.z = this->z - v2.z;
    return res;
}

Vector Vector::normalize() {
    float norm = sqrt(x*x+y*y+z*z);
    Vector res(x/norm,y/norm,z/norm);
    return res;
}

Vector Vector::cross(Vector v2){
    return Vector(this->y*v2.z-this->z*v2.y, this->z*v2.x-this->x*v2.z, x*v2.y-y*v2.x);
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