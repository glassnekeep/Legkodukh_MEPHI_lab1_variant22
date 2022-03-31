//
// Created by - on 23.03.2022.
//

#include "tests.h"

int testMatrixSum(Matrix* matrix1, Matrix* matrix2, Matrix* expectedResult) {
    if (matrixEquals(matrixSum(matrix1, matrix2), expectedResult)) {
        return 1;
    } else {
        return 0;
    }
}

int testMatrixMultiply(Matrix* matrix1, Matrix* matrix2, Matrix* expectedResult) {
    if (matrixEquals(matrixMultiply(matrix1, matrix2), expectedResult)) {
        return 1;
    } else {
        return 0;
    }
}

int testTransposeMatrix(Matrix* matrix, Matrix* expectedResult) {
    if (matrixEquals(transpose(matrix), expectedResult)) {
        return 1;
    } else {
        return 0;
    }
}

int testLinearCombinationOfLines(Matrix* matrix, const double* coefficients, int line, Matrix* expectedResult) {
    addLinearCombinationOfLines(matrix, coefficients, line);
    if (matrixEquals(matrix, expectedResult)) {
        return 1;
    } else {
        return 0;
    }
}

int testLinearCombinationOfColumns(Matrix* matrix, const double* coefficients, int column, Matrix* expectedResult) {
    addLinearCombinationOfColumns(matrix, coefficients, column);
    if (matrixEquals(matrix, expectedResult)) {
        return 1;
    } else {
        return 0;
    }
}
