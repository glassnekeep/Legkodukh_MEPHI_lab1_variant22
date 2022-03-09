//
// Created by - on 08.03.2022.
//

#include "Matrix.h"
#include <string.h>

Matrix* matrixSum(Matrix* matrix1, Matrix* matrix2) {
    if (!ringInfoEquals(matrix1 -> ringInfo, matrix2 -> ringInfo)) {
        printf("Matrices have different data types!\n");
        return NULL;
    }
    if (matrix1 -> m != matrix2 -> m) {
        printf("Matrices have different number of lines!\n");
        return NULL;
    }
    if (matrix1 -> n != matrix2 -> n) {
        printf("Matrices have different number of columns");
        return NULL;
    }
    int m = matrix1 -> m;
    int n = matrix1 -> n;
    size_t size = matrix1 -> ringInfo -> size;
    Matrix* result = malloc(sizeof(Matrix));
    void** array = calloc(m, sizeof(void*));
    for (int i = 0; i < m; i++) {
        array[i] = calloc(n, size);
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            memcpy(array[i] + j * size, matrix1 -> ringInfo -> sum(matrix1 -> array[i] + j * size, matrix2 -> array[i] + j * size), size);
        }
    }
    result -> m = m;
    result -> n = n;
    result -> ringInfo == matrix1 -> ringInfo;
    result -> array = array;
    return result;
}

Matrix* matrixMultiply(Matrix* matrix1, Matrix* matrix2) {
    if (!ringInfoEquals(matrix1 -> ringInfo, matrix2 -> ringInfo)) {
        printf("Matrices have different data types!\n");
        return NULL;
    }
    if (matrix1 -> n != matrix2 -> m) {
        printf("Multiplication is impossible, number of lines of first matrix is not equal to number 0f columns of second matrix!\n");
        return NULL;
    }
    int m = matrix1 -> m;
    int n = matrix1 -> n;
    size_t size = matrix1 -> ringInfo -> size;
    Matrix* result = malloc(sizeof(Matrix));
    result -> m = m;
    result -> n = n;
    result -> ringInfo = matrix1 -> ringInfo;
    void** array = calloc(m, sizeof(void*));
    for (int i = 0; i < m; i++) {
        array[i] = calloc(n, size);
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            void *sum = malloc(size);
            sum = result -> ringInfo -> zero;
            for (int k = 0; k < m; k++) {
                sum = result -> ringInfo -> sum (sum, result -> ringInfo -> multiply(matrix1 -> array[i] + k * size, matrix2 -> array[k] + j * size));
            }
            memcpy(array[i] + j * size, sum, size);
        }
    }
    result -> array = array;
    return result;
}
//TODO првоерить корректность работы этой штуки
void transposition(Matrix* matrix) {
    Matrix* result = malloc(sizeof(Matrix));
    int m = matrix -> m;
    int n = matrix -> n;
    size_t size = matrix -> ringInfo -> size;
    result -> m = n;
    result -> n = m;
    result -> ringInfo = matrix -> ringInfo;
    void** array = calloc(m, sizeof(void*));
    for (int i = 0; i < m; i++) {
        array[i] = calloc(n, size);
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            memcpy(array[j] + i * size, matrix -> array[i] + j * size, size);
        }
    }
    *matrix = *result;
    for (int i = 0; i < m; i++) {
        free(result -> array[i]);
    }
    free(result -> array);
    free(result -> ringInfo);
    free(result);
}

void addLinearCombinationOfLines(Matrix* matrix, const double* coefficients, int line) {
    int m = matrix -> m;
    int n = matrix -> n;
    size_t size = matrix -> ringInfo -> size;
    if (line >= m) {
        printf("Line number in bigger than the number of lines in matrix!\n");
        return;
    }
    if (line < 0) {
        printf("Line number is less than 0!\n");
        return;
    }
    //TODO обработать ошибку когда количество коэффициентов не равно количество строк - 1
    for (int j = 0; j < n; j++) {
        //void* sum = matrix -> ringInfo -> zero;
        void* sum = malloc(size);
        memcpy(sum, matrix -> array[line] + j * size, size);
        for (int i = 0; i < m; i++) {
            if (i != line) {
                sum = matrix -> ringInfo -> sum(sum, matrix -> ringInfo -> multiplyOnDouble(matrix -> array[i] + j * size, coefficients[i]));
            }
        }
        memcpy(matrix -> array[line] + j * size, sum, size);
    }
}

void addLinearCombinationOfColumns(Matrix* matrix, const double* coefficients, int column) {
    int m = matrix -> m;
    int n = matrix -> n;
    size_t size = matrix -> ringInfo -> size;
    if (column >= n) {
        printf("Column number is bigger that the number of columns in matrix!\n");
        return;
    }
    if (column < 0) {
        printf("Column number is lower that 0");
        return;
    }
    //TODO обработать ошибку когда количество коэффициентов не равно количество столбцов - 1
    
}

Matrix* intInput(int m, int n, RingInfo* ringInfo) {
    if (m < 0) {
        printf("Number of lines is lower than 1!\n");
        return NULL;
    }
    if (n < 0) {
        printf("Number of columns is lower than 1!\n!");
        return NULL;
    }
    if (ringInfo == NULL) {
        printf("The data type is not defined!\n");
        return NULL;
    }
    int** array = (int **)calloc(m, sizeof(int*));
    for (int i = 0; i < m; i++) {
        array[i] = (int *) calloc(n, ringInfo -> size);
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &array[i][j]);
        }
    }
    Matrix* matrix = malloc(sizeof(Matrix));
    matrix -> m = m;
    matrix -> n = n;
    matrix -> ringInfo = ringInfo;
    matrix -> array = (void*)array;

}