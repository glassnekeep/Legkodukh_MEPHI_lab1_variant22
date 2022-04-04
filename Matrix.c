//
// Created by - on 08.03.2022.
//

#include "Matrix.h"

errorSafeReturnMatrix* matrixSum(Matrix* matrix1, Matrix* matrix2) {
    errorSafeReturnMatrix* returnValue = malloc(sizeof(errorSafeReturnMatrix));
    Matrix* result = malloc(sizeof(Matrix));
    if (matrix1 == NULL || matrix2 == NULL) {
        //printf("One of matrices not created yet!\n");
        returnValue -> error = NULL_POINTER;
        returnValue -> value = NULL;
        return returnValue;
    }
    if (!ringInfoEquals(matrix1 -> ringInfo, matrix2 -> ringInfo)) {
        //printf("Matrices have different data types!\n");
        returnValue -> error = DIFFERENT_TYPES;
        returnValue -> value = NULL;
        return returnValue;
    }
    if (matrix1 -> m != matrix2 -> m) {
        //printf("Matrices have different number of lines!\n");
        returnValue -> error = DIFFERENT_NUMBER_OF_LINES;
        returnValue -> value = NULL;
        return returnValue;
    }
    if (matrix1 -> n != matrix2 -> n) {
        //printf("Matrices have different number of columns");
        returnValue -> error = DIFFERENT_NUMBER_OF_COLUMNS;
        returnValue -> value = NULL;
        return returnValue;
    }
    int m = matrix1 -> m;
    int n = matrix1 -> n;
    size_t size = matrix1 -> ringInfo -> size;
    void** array = calloc(m, sizeof(void*));
    for (int i = 0; i < m; i++) {
        *((char**) array + i) = calloc(n, sizeof(matrix1 -> ringInfo -> size));
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            memcpy(*((char**)array + i) + j * size, matrix1 -> ringInfo -> sum(*((char**)(matrix1 -> array) + i) + j * size, * ((char**)(matrix2 -> array) + i) + j * size), size);
        }
    }
    result -> m = m;
    result -> n = n;
    result -> ringInfo = matrix1 -> ringInfo;
    result -> array = array;
    returnValue -> value = result;
    returnValue -> error = OK;
    return returnValue;
}

errorSafeReturnMatrix* matrixMultiply(Matrix* matrix1, Matrix* matrix2) {
    errorSafeReturnMatrix* returnValue = malloc(sizeof(errorSafeReturnMatrix));
    Matrix* result = malloc(sizeof(Matrix));
    if (matrix1 == NULL || matrix2 == NULL) {
        //printf("One of matrices not created yet!\n");
        returnValue -> error = NULL_POINTER;
        returnValue -> value = NULL;
        return returnValue;
    }
    if (!ringInfoEquals(matrix1 -> ringInfo, matrix2 -> ringInfo)) {
        //printf("Matrices have different data types!\n");
        returnValue -> error = DIFFERENT_TYPES;
        returnValue -> value = NULL;
        return returnValue;
    }
    if (matrix1 -> n != matrix2 -> m) {
        //printf("Multiplication is impossible, number of lines of first matrix is not equal to number 0f columns of second matrix!\n");
        returnValue -> error = IMPOSSIBLE_MULTIPLICATION;
        returnValue -> value = NULL;
        return returnValue;
    }
    int m = matrix1 -> m;
    int s = matrix1 -> n;
    int n = matrix2 -> n;
    size_t size = matrix1 -> ringInfo -> size;
    result -> m = m;
    result -> n = n;
    result -> ringInfo = matrix1 -> ringInfo;
    void** array = calloc(m, sizeof(void*));
    for (int i = 0; i < m; i++) {
        *((char**) array + i) = calloc(n, sizeof(matrix1 -> ringInfo -> size));
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            void *sum = malloc(size);
            sum = result -> ringInfo -> zero;
            for (int k = 0; k < s; k++) {
                sum = result -> ringInfo -> sum (sum, result -> ringInfo -> multiply(*((char**)(matrix1 -> array) + i) + k * size, *((char**) (matrix2 -> array) + k) + j * size));
            }
            memcpy(*((char**)array + i) + j * size, sum, size);
        }
    }
    //freeMatrix(matrix1);
    result -> array = array;
    returnValue -> value = result;
    returnValue -> error = OK;
    return returnValue;
}
//TODO првоерить корректность работы этой штуки
errorSafeReturnMatrix* transpose(Matrix* matrix) {
    errorSafeReturnMatrix* returnValue = malloc(sizeof(errorSafeReturnMatrix));
    Matrix* result = malloc(sizeof(Matrix));
    if (matrix == NULL) {
        //printf("Matrix not created yet!\n");
        returnValue -> value = NULL;
        returnValue -> error = NULL_POINTER;
        return returnValue;
    }
    int m = matrix -> m;
    int n = matrix -> n;
    size_t size = matrix -> ringInfo -> size;
    result -> m = n;
    result -> n = m;
    result -> ringInfo = malloc(sizeof(RingInfo));
    result -> ringInfo = matrix -> ringInfo;
    void** array = calloc(n, sizeof(void*));
    for (int i = 0; i < n; i++) {
        *((char**) array + i) = calloc(m, sizeof(matrix -> ringInfo -> size));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            memcpy(*((char**)array + i) + j * size, *((char**)(matrix -> array) + j) + i * size, size);
        }
    }
    result -> array = array;
    returnValue -> value = result;
    returnValue -> error = OK;
    return returnValue;
}

errorSafeReturnMatrix* addLinearCombinationOfLines(Matrix* matrix, const double* coefficients, int line) {
    errorSafeReturnMatrix* returnValue = malloc(sizeof(errorSafeReturnMatrix));
    returnValue -> value = malloc(sizeof(Matrix));
    returnValue -> value = NULL;
    if (matrix == NULL) {
        //printf("Matrix not created yet!\n");
        returnValue -> error = NULL_POINTER;
        return returnValue;
    }
    int m = matrix -> m;
    int n = matrix -> n;
    size_t size = matrix -> ringInfo -> size;
    if (line >= m) {
        //printf("Line number in bigger than the number of lines in matrix!\n");
        returnValue -> error = BIG_NUMBER_LINE;
        return returnValue;
    }
    if (line < 0) {
        //printf("Line number is less than 0!\n");
        returnValue -> error = SMALL_NUMBER_LINE;
        return returnValue;
    }
    //TODO обработать ошибку когда количество коэффициентов не равно количество строк - 1
    for (int j = 0; j < n; j++) {
        //void* sum = matrix -> ringInfo -> zero;
        void* sum = malloc(size);
        memcpy(sum, *((char**)(matrix -> array) + line) + j * size, size);
        for (int i = 0; i < m; i++) {
            if (i != line) {
                sum = matrix -> ringInfo -> sum(sum, matrix -> ringInfo -> multiplyOnDouble(*((char**)(matrix -> array) + i) + j * size, coefficients[i]));
            }
        }
        memcpy(*((char**)(matrix -> array) + line) + j * size, sum, size);
        free(sum);
    }
    returnValue -> error = OK;
    return returnValue;
}

errorSafeReturnMatrix* addLinearCombinationOfColumns(Matrix* matrix, const double* coefficients, int column) {
    errorSafeReturnMatrix* returnValue = malloc(sizeof(errorSafeReturnMatrix));
    returnValue -> value = malloc(sizeof(Matrix));
    returnValue -> value = NULL;
    if (matrix == NULL) {
        //printf("Matrix not created yet!\n");
        returnValue -> error = NULL_POINTER;
        return returnValue;
    }
    int m = matrix -> m;
    int n = matrix -> n;
    size_t size = matrix -> ringInfo -> size;
    if (column >= n) {
        //printf("Column number is bigger that the number of columns in matrix!\n");
        returnValue -> error = BIG_NUMBER_COLUMN;
        return returnValue;
    }
    if (column < 0) {
        //printf("Column number is lower that 0");
        returnValue -> error = SMALL_NUMBER_COLUMN;
        return returnValue;
    }
    //TODO обработать ошибку когда количество коэффициентов не равно количество столбцов - 1
    for (int i = 0; i < m; i++) {
        void* sum = malloc(size);
        memcpy(sum, *(char**)((matrix -> array) + i) + column * size, size);
        for (int j =0; j < n; j++) {
            if (j != column) {
                sum = matrix -> ringInfo -> sum(sum, matrix -> ringInfo -> multiplyOnDouble(*((char**)(matrix -> array) + i) + j * size, coefficients[j]));
            }
        }
        memcpy(*((char**)(matrix -> array) + i) + column * size, sum, size);
        free(sum);
    }
    returnValue -> error = OK;
    returnValue -> value = matrix;
    return returnValue;
}

void printMatrix(Matrix* matrix, int dataType) {
    if (matrix == NULL) {
        printf("Matrix not created yet!\n");
        return;
    }
    if (dataType < 1 || dataType > 3) {
        printf("ERROR! Data type flag error\n");
        return;
    }
    int m = matrix -> m;
    int n = matrix -> n;
    void** array = matrix -> array;
    printf("----------------------------------\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            switch (dataType) {
                case 1:
                    printf("%-5d", ((int**)array)[i][j]);
                    break;
                case 2:
                    printf("%-5.2f", ((double**)array)[i][j]);
                    break;
                case 3:
                    printf("%.1f + %1.1fi   ", ((ComplexNumber **)array)[i][j].realPart, ((ComplexNumber **)array)[i][j].imaginaryPart);
                    break;
                default:
                    printf("ERROR! Data type flag error\n");
                    break;
            }
        }
        printf("\n");
    }
    printf("----------------------------------\n");
}

void printfMatrixToFile(Matrix* matrix, int dataType, FILE* filename) {
    if (matrix == NULL) {
        fprintf(filename, "Matrix not created yet!\n");
        return;
    }
    if (dataType < 1 || dataType > 3) {
        fprintf(filename, "ERROR! Data type flag error\n");
        return;
    }
    int m = matrix -> m;
    int n = matrix -> n;
    void** array = matrix -> array;
    fprintf(filename, "----------------------------------\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            switch (dataType) {
                case 1:
                    fprintf(filename,"%-5d", ((int**)array)[i][j]);
                    break;
                case 2:
                    fprintf(filename,"%-5.2f", ((double**)array)[i][j]);
                    break;
                case 3:
                    fprintf(filename, "%.1f + %1.1fi   ", ((ComplexNumber **)array)[i][j].realPart, ((ComplexNumber **)array)[i][j].imaginaryPart);
                    break;
                default:
                    fprintf(filename, "ERROR! Data type flag error\n");
                    break;
            }
        }
        fprintf(filename, "\n");
    }
    fprintf(filename, "----------------------------------\n");
}

void createRingInfoBasedOnDataType(RingInfo* ringInfo, int dataType) {
    if (dataType < 1 || dataType > 3) {
        printf("ERROR! Data type flag error\n");
        return;
    }
    switch (dataType) {
        case 1:
            createIntRingInfo(ringInfo);
            break;
        case 2:
            createDoubleRingInfo(ringInfo);
            break;
        case 3:
            createComplexRingInfo(ringInfo);
            break;
        default:
            break;
    }
}

Matrix* inputMatrix(int m, int n, int dataType) {
    if (dataType < 1 || dataType > 3) {
        printf("ERROR! Data type flag error\n");
        return NULL;
    }
    RingInfo* ringInfo = malloc(sizeof(RingInfo));
    Matrix* result = malloc(sizeof(Matrix));
    createRingInfoBasedOnDataType(ringInfo, dataType);
    void** array = calloc(m, sizeof(void*));
    for (int i = 0; i < m; i++) {
        *((char**) array + i) = calloc(n, sizeof(ringInfo -> size));
    }
    result -> ringInfo = ringInfo;
    result -> m = m;
    result -> n = n;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("Enter the value of element[%d][%d]\n", i, j);
            switch (dataType) {
                case 1:
                    int newIntValue;
                    scanf("%d", &newIntValue);
                    ((int**) array)[i][j] = newIntValue;
                    break;
                case 2:
                    double newDoubleValue;
                    scanf("%lf", &newDoubleValue);
                    ((double**) array)[i][j] = newDoubleValue;
                    break;
                case 3:
                    double real;
                    double imaginary;
                    printf("Enter the real part\n");
                    scanf("%lf", &real);
                    printf("Enter the imaginary part\n");
                    scanf("%lf", &imaginary);
                    ComplexNumber newComplex = {real, imaginary};
                    ((ComplexNumber**) array)[i][j] = newComplex;
                    break;
                default:
                    break;
            }
        }
    }
    result -> array = array;
    return result;
}

void freeMatrix(Matrix* matrix) {
    if (matrix == NULL) {
        return;
    }
    RingInfo* ringInfo = matrix -> ringInfo;
    void** array = matrix -> array;
    int m = matrix -> m;
    for (int i = 0; i < m; i++) {
        free(array[i]);
    }
    free(array);
    free(ringInfo);
    free(matrix);
}

int matrixEquals(Matrix* matrix1, Matrix* matrix2) {
    int m = matrix1 -> m;
    int n = matrix1 -> n;
    size_t size = matrix1 -> ringInfo -> size;
    if (matrix1 -> m == matrix2 -> m && matrix1 -> n == matrix2 -> n && ringInfoEquals(matrix1 -> ringInfo, matrix2 -> ringInfo)) {
        int flag = 1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int value1 = ((int**)matrix1 -> array)[i][j];
                int value2 = ((int**)matrix2 -> array)[i][j];
                if (value1 != value2) {
                    flag = 0;
                    return 0;
                }
            }
        }
    }
    return 1;
}