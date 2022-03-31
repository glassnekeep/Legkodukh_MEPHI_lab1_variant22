//
// Created by - on 08.03.2022.
//

#include "Matrix.h"

Matrix* matrixSum(Matrix* matrix1, Matrix* matrix2) {
    if (matrix1 == NULL || matrix2 == NULL) {
        printf("One of matrices not created yet!\n");
        return NULL;
    }
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
        *((char**) array + i) = calloc(n, sizeof(matrix1 -> ringInfo -> size));
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            //memcpy(array + j * size, matrix1 -> ringInfo -> sum(matrix1 -> array[i] + j * size, matrix2 -> array[i] + j * size), size);
            //memcpy(*((char**) result + i) + j * size, matrix1 -> ringInfo -> sum(*((char **) matrix1 -> array + i) + j * size, *((char**) matrix2 -> array + i) + j * size), size);
            memcpy(*((char**)array + i) + j * size, matrix1 -> ringInfo -> sum(*((char**)(matrix1 -> array) + i) + j * size, * ((char**)(matrix2 -> array) + i) + j * size), size);
        }
    }
    result -> m = m;
    result -> n = n;
    result -> ringInfo = matrix1 -> ringInfo;
    result -> array = array;
    return result;
}

Matrix* matrixMultiply(Matrix* matrix1, Matrix* matrix2) {
    if (matrix1 == NULL || matrix2 == NULL) {
        printf("One of matrices not created yet!\n");
        return NULL;
    }
    if (!ringInfoEquals(matrix1 -> ringInfo, matrix2 -> ringInfo)) {
        printf("Matrices have different data types!\n");
        return NULL;
    }
    if (matrix1 -> n != matrix2 -> m) {
        printf("Multiplication is impossible, number of lines of first matrix is not equal to number 0f columns of second matrix!\n");
        return NULL;
    }
    int m = matrix1 -> m;
    int s = matrix1 -> n;
    int n = matrix2 -> n;
    size_t size = matrix1 -> ringInfo -> size;
    Matrix* result = malloc(sizeof(Matrix));
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
    return result;
}
//TODO првоерить корректность работы этой штуки
Matrix* transpose(Matrix* matrix) {
    if (matrix == NULL) {
        printf("Matrix not created yet!\n");
        return NULL;
    }
    Matrix* result = malloc(sizeof(Matrix));
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
    return result;
}

void addLinearCombinationOfLines(Matrix* matrix, const double* coefficients, int line) {
    if (matrix == NULL) {
        printf("Matrix not created yet!\n");
        return;
    }
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
        memcpy(sum, *((char**)(matrix -> array) + line) + j * size, size);
        for (int i = 0; i < m; i++) {
            if (i != line) {
                sum = matrix -> ringInfo -> sum(sum, matrix -> ringInfo -> multiplyOnDouble(*((char**)(matrix -> array) + i) + j * size, coefficients[i]));
            }
        }
        memcpy(*((char**)(matrix -> array) + line) + j * size, sum, size);
        free(sum);
    }
}

void addLinearCombinationOfColumns(Matrix* matrix, const double* coefficients, int column) {
    if (matrix == NULL) {
        printf("Matrix not created yet!\n");
        return;
    }
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

//TODO можно реализовать работу с диапазоном возможных значений от пользователя
Matrix* generateRandomMatrix(int dataType) {
    srand(time(NULL));
    int m = 1 + rand() % 20;
    int n = 1 + rand() % 20;
    if (dataType < 1 || dataType > 3) {
        printf("ERROR! Data type flag error\n");
        return NULL;
    }
    Matrix* matrix = malloc(sizeof(Matrix));
    RingInfo* ringInfo = malloc(sizeof(RingInfo));
    createRingInfoBasedOnDataType(ringInfo, dataType);
    void** array = calloc(m, sizeof(void*));
    for (int i = 0; i < m; i++) {
        *((char**) array + i) = calloc(n, sizeof(ringInfo -> size));
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            switch(dataType) {
                case 1:
                    ((int**) array)[i][j] = rand() % 100 * (int) pow(-1.0, (double) (rand() % 2 + 1));
                    break;
                case 2:
                    ((double**) array)[i][j] = (double) (rand() % 100) * pow(-1.0, (double) (rand() % 2 + 1));
                    break;
                case 3:
                    double real = rand() % 100 * pow(-1.0, (double) (rand() % 2 + 1));
                    double imaginary = rand() % 100 * pow(-1.0, (double) (rand() % 2 + 1));
                    ComplexNumber newValue = {real, imaginary};
                    ((ComplexNumber**) array)[i][j] = newValue;
                    break;
                default:
                    return NULL;
            }
        }
    }
    matrix -> ringInfo = ringInfo;
    matrix -> m = m;
    matrix -> n = n;
    matrix -> array = array;
    return matrix;
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
                if (*((char**)(matrix1 -> array) + i) + j * size != *((char**)(matrix2 -> array) + i) + j * size) {
                    flag = 0;
                    return 0;
                }
            }
        }
    }
    return 1;
}