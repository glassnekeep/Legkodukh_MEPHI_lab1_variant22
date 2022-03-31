#include <stdio.h>
#include "Matrix.h"
#include <time.h>

/*<--------------ТЗ-------------->
 * Прямоугольная матрица
 * Типы данных: целые вчисла, вещественные числа, комплексные числа
 * Базовые операции: матричное сложение и умножение, транспонирование, прибавление к строке линейной комбинации других строк
 *
 * Варивант №22
 * Прямоугольная матрица, целые и комплексные числа, матричное сложение и умножение, транспонирование
 * <-------------ТЗ--------------> */

void clearScreen() {
    system("cls");
    fflush(stdout);
}

Matrix* createTestMatrix(RingInfo* ringInfo, int m, int n) {
    Matrix* matrix = malloc(sizeof(Matrix));
    size_t size = ringInfo -> size;
    matrix -> ringInfo = ringInfo;
    void** array = calloc(m, sizeof(void*));
    for (int i = 0; i < m; i++) {
        *((char**) array + i) = calloc(n, sizeof(size));
    }
    return matrix;
}

/*void fillTestMatrices() {
    int* intArray1 = calloc(4, sizeof(int));
    int* intArray2 = calloc(4, sizeof(int));
    int* intArray3 = calloc(4, sizeof(int));
    int* intArray4 = calloc(4, sizeof(int));
    double* doubleArray1 = calloc(4, sizeof(double));
    double* doubleArray2 = calloc(4, sizeof(double));
    double* doubleArray3 = calloc(4, sizeof(double));
    double* doubleArray4 = calloc(4, sizeof(double));
    ComplexNumber* complexArray1 = calloc(4, sizeof(ComplexNumber));
    ComplexNumber* complexArray2 = calloc(4, sizeof(ComplexNumber));
    ComplexNumber* complexArray3 = calloc(4, sizeof(ComplexNumber));
    ComplexNumber* complexArray4 = calloc(4, sizeof(ComplexNumber));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            intArray1[2 * i + j] = 1 + 2 * i + j;
            intArray2[2 * i + j] = 1 + 2 * i + j;
            doubleArray1[2 * i + j] = 1.0 + (double) (2 * i) + (double) j;
            doubleArray2[2 * i + j] = 1.0 + (double) (2 * i) + (double) j;
        }
    }
    ComplexNumber a1 = {1.0, 1.0};
    ComplexNumber a2 = {2.0, 2.0};
    ComplexNumber a3 = {3.0, 3.0};
    ComplexNumber a4 = {4.0, 4.0};
    ComplexNumber a5 = {2.0, 2.0};
    ComplexNumber a6= {4.0, 4.0};
    ComplexNumber a7 = {6.0, 6.0};
    ComplexNumber a8 = {8.0, 8.0};
    ComplexNumber a9 = {0.0, 14.};
    ComplexNumber a10 = {0.0, 20.0};
    ComplexNumber a11 = {0.0, 30.0};
    ComplexNumber a12 = {0.0, 44.0};
    complexArray1[0] = a1;
    complexArray1[1] = a2;
    complexArray1[2] = a3;
    complexArray1[3] = a4;
    complexArray2[0] = a1;
    complexArray2[1] = a2;
    complexArray2[2] = a3;
    complexArray2[3] = a4;
    complexArray3[0] = a5;
    complexArray3[1] = a6;
    complexArray3[2] = a7;
    complexArray3[3] = a8;
    complexArray4[0] = a9;
    complexArray4[1] = a10;
    complexArray4[2] = a11;
    complexArray4[3] = a12;
    intArray3[0] = 2;
    intArray3[1] = 4;
    intArray3[2] = 6;
    intArray3[3] = 8;
    intArray4[0] = 7;
    intArray4[1] = 10;
    intArray4[2] = 15;
    intArray4[3] = 22;
    doubleArray3[0] = 1.0;
    doubleArray3[1] = 2.0;
    doubleArray3[2] = 3.0;
    doubleArray3[3] = 4.0;
    doubleArray4[0] = 7.0;
    doubleArray4[1] = 10.0;
    doubleArray4[2] = 15.0;
    doubleArray4[3] = 22.0;
    RingInfo* intRingInfo = malloc(sizeof(RingInfo));
    RingInfo* doubleRingInfo = malloc(sizeof(RingInfo));
    RingInfo* complexRingInfo = malloc(sizeof(RingInfo));
    createIntRingInfo(intRingInfo);
    createDoubleRingInfo(doubleRingInfo);
    createComplexRingInfo(complexRingInfo);
    Matrix* intMatrix1 = createTestMatrix(intRingInfo, intArray1);
    Matrix* intMatrix2 = createTestMatrix(intRingInfo, intArray1);
    Matrix* intSumMatrix = createTestMatrix(intRingInfo, intArray3);
    Matrix* intMultiplyMatrix = createTestMatrix(intRingInfo, intArray4);
    Matrix* doubleMatrix1 = createTestMatrix(intRingInfo, doubleArray1);
    Matrix* doubleMatrix2 = createTestMatrix(intRingInfo, doubleArray2);
    Matrix* doubleMatrix3 = createTestMatrix(intRingInfo, doubleArray3);
    Matrix* doubleMatrix4 = createTestMatrix(intRingInfo, doubleArray4);
    Matrix* complexMatrix1 = createTestMatrix(intRingInfo, complexArray1);
    Matrix* complexMatrix2 = createTestMatrix(intRingInfo, complexArray2);
    Matrix* complexMatrix3 = createTestMatrix(intRingInfo, complexArray3);
    Matrix* complexMatrix4 = createTestMatrix(intRingInfo, complexArray4);
    printf("Testing sum\n");
    printf("Integer\n");
}*/

/*void doTests() {
    size_t intSize = sizeof(int);
    size_t doubleSize = sizeof(double);
    size_t complexSize = sizeof(ComplexNumber);
    int m = 2;
    int n = 2;
    Matrix* testIntMatrix1 = malloc(sizeof(Matrix));
    Matrix* testIntMatrix2 = malloc(sizeof(Matrix));
    Matrix* testDoubleMatrix1 = malloc(sizeof(Matrix));
    Matrix* testDoubleMatrix2 = malloc(sizeof(Matrix));
    Matrix* testComplexMatrix1 = malloc(sizeof(Matrix));
    Matrix* testComplexMatrix2 = malloc(sizeof(Matrix));
    RingInfo* intRingInfo = malloc(sizeof(RingInfo));
    RingInfo* doubleRingInfo = malloc(sizeof(RingInfo));
    RingInfo* complexRingInfo = malloc(sizeof(RingInfo));
    createIntRingInfo(intRingInfo);
    createDoubleRingInfo(doubleRingInfo);
    createComplexRingInfo(complexRingInfo);
    testIntMatrix1 -> ringInfo = intRingInfo;
    testIntMatrix2 -> ringInfo = intRingInfo;
    testDoubleMatrix1 -> ringInfo = doubleRingInfo;
    testDoubleMatrix2 -> ringInfo = doubleRingInfo;
    testComplexMatrix1 -> ringInfo = complexRingInfo;
    testComplexMatrix2 -> ringInfo = complexRingInfo;
    testIntMatrix1 -> m = m;
    testIntMatrix1 -> n = n;
    testIntMatrix2 -> m = m;
    testIntMatrix2 -> n = n;
    testDoubleMatrix1 -> m = m;
    testDoubleMatrix1 -> n = n;
    testDoubleMatrix2 -> m = m;
    testDoubleMatrix2 -> n = n;
    testComplexMatrix1 -> m = m;
    testComplexMatrix1 -> n = n;
    testComplexMatrix2 -> m = m;
    testComplexMatrix2 -> n = n;
    int* intStart = getIntZero();
    double* doubleStart = getDoubleZero();
    ComplexNumber* complexStart = getComplexZero();
    int* intStep = getIntOne();
    double* doubleStep = getDoubleOne();
    ComplexNumber* complexStep = getComplexOne();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            intStart = intRingInfo -> sum(intStart, intStep);
            doubleStart = doubleRingInfo -> sum(doubleStart, doubleStep);
            complexStart = complexRingInfo -> sum(complexStart, complexStep);
            ((int**) testIntMatrix1 -> array)[i][j] = *intStart;
            ((int**) testIntMatrix2 -> array)[i][j] = *intStart;
            ((double**) testDoubleMatrix1 -> array)[i][j] = *doubleStart;
            ((double**) testDoubleMatrix2 -> array)[i][j] = *doubleStart;
            ((ComplexNumber**) testComplexMatrix1 -> array)[i][j] = complexStart;
            ((ComplexNumber**) testComplexMatrix2 -> array)[i][j] = complexStart;
        }
    }
}*/



void testWithFile() {
    char* testIntFileName = "test.txt";
    char* testDoubleFileName = "testDouble.txt";
    char* testComplexFileName = "testComplex.txt";
    char* testOutputFileName = "testOutput.txt";
    FILE* testIntFile;
    FILE* testDoubleFile;
    FILE* testComplexFile;
    FILE* testOutPutFile;
    RingInfo* intRingInfo = malloc(sizeof(RingInfo));
    RingInfo* doubleRingInfo = malloc(sizeof(RingInfo));
    RingInfo* complexRingInfo = malloc(sizeof(RingInfo));
    createIntRingInfo(intRingInfo);
    createDoubleRingInfo(doubleRingInfo);
    createComplexRingInfo(complexRingInfo);
    int m;
    int n;
    int line;
    int column;
    testIntFile = fopen("test.txt\0", "r");
    testOutPutFile = fopen("testOutput.txt", "w");
    fscanf(testIntFile, "%d", &m);
    fscanf(testIntFile, "%d", &n);
    Matrix* matrix1 = createTestMatrix(intRingInfo, m, n);
    Matrix* matrix2 = createTestMatrix(intRingInfo, m, n);
    Matrix* matrix3 = createTestMatrix(intRingInfo, m, n);
    Matrix* matrix4 = createTestMatrix(intRingInfo, m, n);
    Matrix* matrix5 = createTestMatrix(intRingInfo, m, n);
    Matrix* matrix6 = createTestMatrix(intRingInfo, m, n);
    Matrix* matrix7 = createTestMatrix(intRingInfo, m, n);
    int coefficientLineSize = m - 1;
    int coefficientColumnSize = n - 1;
    double* coefficientLineArray = calloc(coefficientLineSize, sizeof(double));
    double* coefficientColumnArray = calloc(coefficientColumnSize, sizeof(double));
    fscanf(testIntFile, "%d", &line);
    fscanf(testIntFile, "%d", &column);
    for (int i = 0; i < coefficientLineSize; i++) {
        fscanf(testIntFile, "%lf", &coefficientLineArray[i]);
    }
    for (int i = 0; i < coefficientColumnSize; i++) {
        fscanf(testIntFile, "%lf", &coefficientColumnArray[i]);
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(testIntFile, "%d", &((int**) matrix1 -> array)[i][j]);
            fscanf(testIntFile, "%d", &((int**) matrix2 -> array)[i][j]);
            fscanf(testIntFile, "%d", &((int**) matrix3-> array)[i][j]);
            fscanf(testIntFile, "%d", &((int**) matrix4 -> array)[i][j]);
            fscanf(testIntFile, "%d", &((int**) matrix5 -> array)[i][j]);
            fscanf(testIntFile, "%d", &((int**) matrix6 -> array)[i][j]);
            fscanf(testIntFile, "%d", &((int**) matrix7 -> array)[i][j]);
        }
    }
    Matrix* matrixSummed = matrixSum(matrix1, matrix2);
    Matrix* matrixMultiplied = matrixMultiply(matrix1, matrix2);
    Matrix* matrixTransposed = transpose(matrix1);
    fprintf(testOutPutFile, "Matrix #1\n");
    printfMatrixToFile(matrix1, 1, testOutPutFile);
    fprintf(testOutPutFile,"Matrix #2\n");
    printfMatrixToFile(matrix2, 1, testOutPutFile);
    fprintf(testOutPutFile,"\n\nExpected sum matrix\n");
    printfMatrixToFile(matrix3, 1, testOutPutFile);
    fprintf(testOutPutFile,"\n\nMatrix we got after doing sum\n");
    printfMatrixToFile(matrixSummed, 1, testOutPutFile);
    fprintf(testOutPutFile, "\n\nExpected multiply matrix\n");
    printfMatrixToFile(matrix4, 1, testOutPutFile);
    fprintf(testOutPutFile,"\n\nMatrix we got after doing multiplication\n");
    printfMatrixToFile(matrixMultiplied, 1, testOutPutFile);
    fprintf(testOutPutFile, "\n\nExpected transpose matrix1\n");
    printfMatrixToFile(matrix5, 1, testOutPutFile);
    fprintf(testOutPutFile,"\n\nMatrix we got after doing transpose to matrix1\n");
    printfMatrixToFile(matrixTransposed, 1, testOutPutFile);
    fprintf(testOutPutFile, "\n\nExpected adding linear combination of lines to matrix1\n");
    printfMatrixToFile(matrix6, 1, testOutPutFile);
    fprintf(testOutPutFile,"\n\nMatrix we got after adding linear combination of lines to matrix1\n");
    addLinearCombinationOfLines(matrix1, coefficientLineArray, line);
    printfMatrixToFile(matrix1, 1, testOutPutFile);
    fprintf(testOutPutFile, "\n\nExpected adding linear combination of columns to matrix1\n");
    printfMatrixToFile(matrix7, 1, testOutPutFile);
    fprintf(testOutPutFile,"\n\nMatrix we got after adding linear combination of columns to matrix1\n");
    addLinearCombinationOfColumns(matrix2, coefficientColumnArray, column);
    printfMatrixToFile(matrix2, 1, testOutPutFile);
    if (matrixEquals(matrixSummed, matrix3)) {
        fprintf(testOutPutFile, "\nTest1 passed");
    } else {
        fprintf(testOutPutFile, "\nTest1 not passed");
    }
    if (matrixEquals(matrixMultiplied, matrix4)) {
        fprintf(testOutPutFile, "\nTest2 passed");
    } else {
        fprintf(testOutPutFile, "\nTest2 not passed");
    }
    if (matrixEquals(matrixTransposed, matrix5)) {
        fprintf(testOutPutFile, "\nTest3 passed");
    } else {
        fprintf(testOutPutFile, "\nTest3 not passed");
    }
    if (matrixEquals(matrix1, matrix6)) {
        fprintf(testOutPutFile, "\nTest4 passed");
    } else {
        fprintf(testOutPutFile, "\nTest4 not passed");
    }
    if (matrixEquals(matrix2, matrix7)) {
        fprintf(testOutPutFile, "\nTest5 passed");
    } else {
        fprintf(testOutPutFile, "\nTest5 not passed");
    }
    fclose(testOutPutFile);
    fclose(testIntFile);
}

double* inputLinearCoefficients(int number, int raw) {
    double* array = malloc(sizeof(double) * number);
    for (int i = 0; i < number; i++) {
        int currentRaw = i;
        if (i >= raw) {
            currentRaw++;
        }
        setbuf(stdout, 0);
        printf("Enter coefficient for line %d\n", currentRaw);
        double newValue = 0.0;
        while (scanf("%lf", &newValue) != 1) {
            setbuf(stdout, 0);
            printf("Wrong type, double required\n");
            getchar();
        }
        array[i] = newValue;
    }
    return array;
}

int main() {
    Matrix* matrix = NULL;
    //RingInfo* ringInfo = malloc(sizeof(RingInfo));
    int choice = 0;
    int dataType = 0;
    int m = 0;
    int n = 0;
    do {
        setbuf(stdout, 0);
        printf("1. Form matrix\n2. Export matrix\n3. Operations\n4. Print tests\n5. Clear screen\n6. Exit\n");
        while (scanf("%d", &choice) != 1 || ((int) choice > 6) || (int) choice < 1) {
            setbuf(stdout, 0);
            printf("Error. Enter correct number\n");
            getchar();
        }
        switch (choice) {
            case 1:
                setbuf(stdout, 0);
                printf("Enter data type, where:\n1 - integer\n2 - double\n3 - complex\n");
                while ((scanf("%d", &dataType) != 1) || ((int) dataType > 3) || (int) dataType < 1) {
                    setbuf(stdout, 0);
                    printf("Error. Enter correct number");
                    getchar();
                }
                int choice1 = 0;
                setbuf(stdout, 0);
                printf("1. Read from keyboard\n2. Random value\n");
                while (scanf("%d", &choice1) != 1 || ((int) choice1 > 2) || (int) choice1 < 1) {
                    setbuf(stdout, 0);
                    printf("Error. Enter correct number\n");
                    getchar();
                }
                //TODO тут надо разобраться с инпутами и когда мы вообще создаем матрицу
                /*switch (dataType) {
                    case 1:
                        //createIntRingInfo(ringInfo);
                        break;
                    case 2:
                        //createDoubleRingInfo(ringInfo);
                        break;
                    case 3:
                        //createComplexRingInfo(ringInfo);
                        break;
                    default:
                        break;
                }*/
                /*if (matrix != NULL) {
                    freeMatrix(matrix);
                }*/
                switch (choice1) {
                    case 1:
                        setbuf(stdout, 0);
                        printf("Enter number of lines\n");
                        while (scanf("%d", &m) != 1) {
                            setbuf(stdout, 0);
                            printf("Error. Enter correct number of lines\n");
                            getchar();
                        }
                        setbuf(stdout, 0);
                        printf("Enter number of columns\n");
                        while (scanf("%d", &n) != 1) {
                            setbuf(stdout, 0);
                            printf("Error. Enter correct number of columns\n");
                            getchar();
                        }
                        matrix = inputMatrix(m, n, dataType);
                        break;
                    case 2:
                        matrix = generateRandomMatrix(dataType);
                        break;
                    default:
                        break;
                }
                break;
            case 2:
                /*printf("1. Write matrix to console\n2. Write matrix to binary file\n");
                while (scanf("%d", &choice1) != 1 || ((int) choice1 > 2) || (int) choice1 < 1) {
                    printf("Error. Enter correct number\n");
                    getchar();
                }
                switch (choice1) {
                    case 1:*/
                        printMatrix(matrix, dataType);
                        /*break;
                    case 2:
                        printf("");
                        char *file = readline("Enter filename\n");
                        FILE *fl;
                        fl = fopen(file, "wb");
                        if (fl) {
                            for (int i = 0; i < m; i++) {
                                for (int j = 0; j < n; j++) {
                                    fprintf(fl, "%-5d", matrix[i][j]);
                                }
                                fprintf(fl, "\n");
                            }
                        }
                        fclose(fl);
                        break;
                }*/
                break;
            case 3:
                setbuf(stdout, 0);
                printf("");
                int index;
                setbuf(stdout, 0);
                printf("1. Sum two matrices\n2. Multiply two matrices\n3. Transpose the matrix\n4. Add linear combination of lines\n5. Add linear combination of columns\n");
                while (scanf("%d", &choice1) != 1 || ((int) choice1 > 5) || (int) choice1 < 1) {
                    setbuf(stdout, 0);
                    printf("Error. Enter correct number\n");
                    getchar();
                }
                setbuf(stdout, 0);
                printf("current matrix is %d X %d\n", matrix -> m, matrix -> n);
                switch (choice1) {
                    case 1:
                        Matrix* sumMatrix = inputMatrix(matrix -> m, matrix -> n, dataType);
                        matrix = matrixSum(matrix, sumMatrix);
                        //freeMatrix((sumMatrix));
                        break;
                    case 2:
                        //TODO разобраться с ограничениями на ввод
                        int newMatrixNumberOfColumns;
                        setbuf(stdout, 0);
                        printf("Enter number of columns in the second matrix\n");
                        while (scanf("%d", &newMatrixNumberOfColumns) != 1 || newMatrixNumberOfColumns < 1) {
                            setbuf(stdout, 0);
                            printf("Wrong number of columns. Enter it again\n");
                        }
                        Matrix* multiplyMatrix = inputMatrix(matrix -> n, newMatrixNumberOfColumns, dataType);
                        matrix = matrixMultiply(matrix, multiplyMatrix);
                        //freeMatrix(multiplyMatrix);
                        break;
                    case 3:
                        matrix = transpose(matrix);
                        setbuf(stdout, 0);
                        printf("New matrix is %d X %d\n", matrix -> m, matrix -> n);
                        break;
                    case 4:
                        int line = 0;
                        while (scanf("%d", &line) != 1 || line < 0) {
                            setbuf(stdout, 0);
                            printf("Error. Enter correct number\n");
                            getchar();
                        }
                        double* coefficients = inputLinearCoefficients(matrix -> m - 1, line);
                        addLinearCombinationOfLines(matrix, coefficients, line);
                        free(coefficients);
                        break;
                    case 5:
                        int column = 0;
                        while (scanf("%d", &column) != 1 || column < 0) {
                            setbuf(stdout, 0);
                            printf("Error. Enter correct column\n");
                            getchar();
                        }
                        double* columnCoefficients = inputLinearCoefficients(matrix -> n - 1, column);
                        addLinearCombinationOfColumns(matrix, columnCoefficients, column);
                        free(columnCoefficients);
                        break;
                    default:
                        break;
                }
                break;
            case 4:
                testWithFile();
                break;
            case 5:
                clearScreen();
                break;
            default:
                exit(0);
                break;
        }
    } while (choice != 6);
    return 0;
}
