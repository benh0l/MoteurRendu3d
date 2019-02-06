//
// Created by Benoît on 06/02/2019.
//

#include <iostream>
#include "Matrix.h"

Matrix::Matrix(int r,int c) {
    this->cols = c;
    this->rows = r;
    this->m = std::vector<std::vector<float>>(r, std::vector<float>(c, 0.f));
}

/*
Matrix::Matrix(std::vector<Vector> vectors) {
    this->rows = vectors.size();
    this->cols = 3;
    for(int i = 0;i<vectors.size(); i++){
        this->m[i][0] = vectors[i].x;
        this->m[i][1] = vectors[i].y;
        this->m[i][2] = vectors[i].z;
    }

}*/

Matrix Matrix::identity(int dim) {
    //std::cout << "ok methode identity debut" << std::endl;
    Matrix mat(dim, dim);
    //std::cout << "ok methode identity constructeur" << std::endl;
    for(int i = 0; i<dim; i++){
        for(int j = 0;j<dim; j++){
            if(i==j)
                mat.m[i][j] = 1;
            else
                mat.m[i][j] = 0;
            //std::cout << "ok methode identity ij : " << i << "  " << j << std::endl;
        }
    }
    return mat;
}

Matrix Matrix::inverse() {
    //to do
}

/*
Vector Matrix::matrix2vector() {
    return Vector(this->m[0][0]/this->m[3][0], this->m[1][0]/this->m[3][0], this->m[2][0]/this->m[3][0]);
}

Point Matrix::matrix2point() {
    return Point((int)(this->m[0][0]/this->m[3][0]), (int)(this->m[1][0]/this->m[3][0]), (int)(this->m[2][0]/this->m[3][0]));
}
*/

Matrix Matrix::operator*(const Matrix& a) {
    //assert(cols == a.rows);
    //std::cout << "multiplication matricielle" << std::endl;
    Matrix result(rows, a.cols);
    for (int i=0; i<rows; i++) {
        for (int j=0; j<a.cols; j++) {
            result.m[i][j] = 0.f;
            for (int k=0; k<cols; k++) {
                result.m[i][j] += m[i][k]*a.m[k][j];
            }
        }
    }
    return result;
}