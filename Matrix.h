//
// Created by - on 08.03.2022.
//

#ifndef LEGKODUKH_MEPHI_LAB1_VARIANT22_MATRIX_H
#define LEGKODUKH_MEPHI_LAB1_VARIANT22_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include "RingInfo.h"

typedef struct MatrixOperations {
    void* (*matrixSum) (void*, void*);
    void* (*matrixMultiply) (void*, void*);
    void (*transposition) (void*);
    //При прибавлении линейной комбинации нужно определить массив дробных коэффициентов других строк, количество которых будет кол-во строк в матрице минус 1
    void (*addLinearCombinationOfLines) (void*, double*);
    //При прибавлении линейной комбинации нужно определить массив Дробных коэффициентов других столбцов, количество которых будет кол-во столбцов в матрице минус 1
    void (*addLinearCombinationOfColumns) (void*, double*, int);
} MatrixOperations;

typedef struct Matrix {
    int m;
    int n;
    RingInfo* ringInfo;
    void** array;
    //MatrixOperations* operations;
} Matrix;
#endif //LEGKODUKH_MEPHI_LAB1_VARIANT22_MATRIX_H
