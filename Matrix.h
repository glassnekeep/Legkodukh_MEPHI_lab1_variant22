//
// Created by - on 08.03.2022.
//

#ifndef LEGKODUKH_MEPHI_LAB1_VARIANT22_MATRIX_H
#define LEGKODUKH_MEPHI_LAB1_VARIANT22_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RingInfo.h"
#include <time.h>
#include <math.h>

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

Matrix* matrixSum(Matrix* matrix1, Matrix* matrix2);

Matrix* matrixMultiply(Matrix* matrix1, Matrix* matrix2);

Matrix* transpose(Matrix* matrix);

void addLinearCombinationOfLines(Matrix* matrix, const double* coefficients, int line);

void addLinearCombinationOfColumns(Matrix* matrix, const double* coefficients, int column);

Matrix* intInput(int m, int n, RingInfo* ringInfo);

Matrix* doubleInput(int m, int n, RingInfo* ringInfo);

Matrix* complexInput(int m, int n, RingInfo* ringInfo);

/*void printIntMatrix(Matrix* matrix);

void printfDoubleMatrix(Matrix* matrix);

void printfComplexMatrix(Matrix* matrix);*/

void printMatrix(Matrix* matrix, int dataType);

void printfMatrixToFile(Matrix* matrix, int dataType, FILE* filename);

Matrix* inputMatrix(int m, int n, int dataType);

Matrix* generateRandomMatrix(int dataType);

void freeMatrix(Matrix* matrix);

int matrixEquals(Matrix* matrix1, Matrix* matrix2);

#endif //LEGKODUKH_MEPHI_LAB1_VARIANT22_MATRIX_H
