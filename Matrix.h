//
// Created by Benoît on 06/02/2019.
//

#ifndef MOTEURRENDU3D_MATRIX_H
#define MOTEURRENDU3D_MATRIX_H


#include <vector>
#include "Vector.h"
#include "Point.h"

struct Matrix {
    std::vector<std::vector<float>> m;
    int rows, cols;
public:
    //Matrix(std::vector<Vector> vectors);
    Matrix(int rows, int cols);
    static Matrix identity(int dim);
    Matrix inverse();
    //Vector matrix2vector();
    //Point matrix2point();
    Matrix operator*(const Matrix& a);
};

#endif //MOTEURRENDU3D_MATRIX_H
