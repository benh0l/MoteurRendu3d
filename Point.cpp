//
// Created by Benoît on 27/01/2019.
//

#include "Point.h"

Point::Point(int x, int y, int z){
    this->x = x;
    this->y = y;
    this->z = z;
}

Point::Point(){

}

int Point::getX(){
    return this->x;
}

int Point::getY() {
    return this->y;
}

int Point::getZ() {
    return this->z;
}

/*
Matrix Point::point2matrix() {
    Matrix mat(4, 1);
    mat.m[0][0] = this->x;
    mat.m[1][0] = this->y;
    mat.m[2][0] = this->z;
    mat.m[3][0] = 1.f;
    return mat;
}*/