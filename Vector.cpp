//
// Created by Benoît on 27/01/2019.
//

#include "Vector.h"
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