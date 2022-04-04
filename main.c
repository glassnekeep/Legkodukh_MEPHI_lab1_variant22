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
    //fflush(stdout);
}

void notifyErrorMessage(errorSafeReturnMatrix* errorValue) {
    Errors error = errorValue -> error;
    switch(error) {
        case OK:
            break;
        case NULL_POINTER:
            printf("One of matrices not created yet!\n");
            break;
        case DIFFERENT_TYPES:
            printf("Matrices have different data types!\n");
            break;
        case DIFFERENT_NUMBER_OF_LINES:
            printf("Matrices have different number of lines!\n");
            break;
        case DIFFERENT_NUMBER_OF_COLUMNS:
            printf("Matrices have different number of columns");
            break;
        case IMPOSSIBLE_MULTIPLICATION:
            printf("Multiplication is impossible, number of lines of first matrix is not equal to number 0f columns of second matrix!\n");
            break;
        case SMALL_NUMBER_LINE:
            printf("Line number is less than 0!\n");
            break;
        case BIG_NUMBER_LINE:
            printf("Line number in bigger than the number of lines in matrix!\n");
            break;
        case BIG_NUMBER_COLUMN:
            printf("Column number is bigger that the number of columns in matrix!\n");
            break;
        case SMALL_NUMBER_COLUMN:
            printf("Column number is lower that 0");
            break;
        default:
            break;
    }
}

Matrix* createTestMatrix(RingInfo* ringInfo, int m, int n) {
    Matrix* matrix = malloc(sizeof(Matrix));
    size_t size = ringInfo -> size;
    matrix -> ringInfo = ringInfo;
    matrix -> m = m;
    matrix -> n = n;
    void** array = calloc(m, sizeof(void*));
    for (int i = 0; i < m; i++) {
        *((int**) array + i) = calloc(n, size);
    }
    matrix -> array = array;
    return matrix;
}

void testWithFile() {
    FILE* testOutPutFile;
    RingInfo* intRingInfo = malloc(sizeof(RingInfo));
    RingInfo* doubleRingInfo = malloc(sizeof(RingInfo));
    RingInfo* complexRingInfo = malloc(sizeof(RingInfo));
    createIntRingInfo(intRingInfo);
    createDoubleRingInfo(doubleRingInfo);
    createComplexRingInfo(complexRingInfo);
    int m;
    int n = 0;
    int line;
    int column;
    FILE *testIntFile = fopen("D:/test.txt", "r");
    if (testIntFile == NULL) {
        printf("NULL file");
    }
    testOutPutFile = fopen("D:/testOutput.txt", "w");
    if (fscanf(testIntFile, "%d", &m) != 1) {
        printf("Handled an error!!!");
    }
    if (fscanf(testIntFile, "%d", &n) != 1) {
        printf("Handled an error!!!");
    }
    Matrix* matrix1 = createTestMatrix(intRingInfo, m, n);
    Matrix* matrix2 = createTestMatrix(intRingInfo, m, n);
    Matrix* matrix3 = createTestMatrix(intRingInfo, m, n);
    Matrix* matrix4 = createTestMatrix(intRingInfo, m, n);
    Matrix* matrix5 = createTestMatrix(intRingInfo, m, n);
    Matrix* matrix6 = createTestMatrix(intRingInfo, m, n);
    Matrix* matrix7 = createTestMatrix(intRingInfo, m, n);
    size_t size = matrix1 -> ringInfo -> size;
    int coefficientLineSize = m - 1;
    int coefficientColumnSize = n - 1;
    double* coefficientLineArray = calloc(coefficientLineSize, sizeof(double));
    double* coefficientColumnArray = calloc(coefficientColumnSize, sizeof(double));
    fscanf(testIntFile, "%d", &line);
    for (int i = 0; i < coefficientLineSize; i++) {
        fscanf(testIntFile, "%lf", &coefficientLineArray[i]);
    }
    fscanf(testIntFile, "%d", &column);
    for (int i = 0; i < coefficientColumnSize; i++) {
        fscanf(testIntFile, "%lf", &coefficientColumnArray[i]);
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(testIntFile, "%d", &((int**)(matrix1 -> array))[i][j]);
            fscanf(testIntFile, "%d", &((int**)(matrix2 -> array))[i][j]);
            fscanf(testIntFile, "%d", &((int**)(matrix3 -> array))[i][j]);
            fscanf(testIntFile, "%d", &((int**)(matrix4 -> array))[i][j]);
            fscanf(testIntFile, "%d", &((int**)(matrix5 -> array))[i][j]);
            fscanf(testIntFile, "%d", &((int**)(matrix6 -> array))[i][j]);
            fscanf(testIntFile, "%d", &((int**)(matrix7 -> array))[i][j]);
        }
    }
    errorSafeReturnMatrix* sumResult = malloc(sizeof(errorSafeReturnMatrix));
    errorSafeReturnMatrix* multiplyResult = malloc(sizeof(errorSafeReturnMatrix));
    errorSafeReturnMatrix* transposeResult = malloc(sizeof(errorSafeReturnMatrix));
    sumResult = matrixSum(matrix1, matrix2);
    multiplyResult = matrixMultiply(matrix1, matrix2);
    transposeResult = transpose(matrix1);
    Matrix* matrixSummed = sumResult -> value;
    notifyErrorMessage(sumResult);
    Matrix* matrixMultiplied = multiplyResult -> value;
    notifyErrorMessage(multiplyResult);
    Matrix* matrixTransposed = transposeResult -> value;
    notifyErrorMessage(transposeResult);
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
                    printf("Error. Enter correct number\n");
                    getchar();
                }
                int choice1 = 0;
                setbuf(stdout, 0);
                printf("1. Read from keyboard\n");
                while (scanf("%d", &choice1) != 1 || ((int) choice1 > 1) || (int) choice1 < 1) {
                    setbuf(stdout, 0);
                    printf("Error. Enter correct number\n");
                    getchar();
                }
                //TODO тут надо разобраться с инпутами и когда мы вообще создаем матрицу
                if (choice1) {
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
                }
                break;
            case 2:
                if (!matrix) {
                    printf("No matrix created yet!\n");
                    break;
                }
                printMatrix(matrix, dataType);
                break;
            case 3:
                if (!matrix) {
                    printf("No matrix created yet!\n");
                    break;
                }
                setbuf(stdout, 0);
                printf("");
                //int index;
                setbuf(stdout, 0);
                printf("1. Sum two matrices\n2. Multiply two matrices\n3. Transpose the matrix\n4. Add linear combination of lines\n5. Add linear combination of columns\n");
                while (scanf("%d", &choice1) != 1 || ((int) choice1 > 5) || (int) choice1 < 1) {
                    setbuf(stdout, 0);
                    printf("Error. Enter correct number\n");
                    getchar();
                }
                setbuf(stdout, 0);
                printf("current matrix is %d X %d\n", matrix -> m, matrix -> n);
                errorSafeReturnMatrix* result;
                switch (choice1) {
                    case 1:
                        Matrix* sumMatrix = inputMatrix(matrix -> m, matrix -> n, dataType);
                        result = matrixSum(matrix, sumMatrix);
                        notifyErrorMessage(result);
                        matrix = result -> value;
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
                        result = matrixMultiply(matrix, multiplyMatrix);
                        matrix = result -> value;
                        notifyErrorMessage(result);
                        break;
                    case 3:
                        result = transpose(matrix);
                        matrix = result -> value;
                        notifyErrorMessage(result);
                        setbuf(stdout, 0);
                        printf("New matrix is %d X %d\n", matrix -> m, matrix -> n);
                        break;
                    case 4:
                        int line = 0;
                        printf("Print number of line you would like to add the linear combination to\n");
                        while (scanf("%d", &line) != 1 || line < 0) {
                            setbuf(stdout, 0);
                            printf("Error. Enter correct number\n");
                            getchar();
                        }
                        double* coefficients = inputLinearCoefficients(matrix -> m - 1, line);
                        result = addLinearCombinationOfLines(matrix, coefficients, line);
                        notifyErrorMessage(result);
                        break;
                    case 5:
                        int column = 0;
                        printf("Print number of column you would like to add the linear combination to\n");
                        while (scanf("%d", &column) != 1 || column < 0) {
                            setbuf(stdout, 0);
                            printf("Error. Enter correct column\n");
                            getchar();
                        }
                        double* columnCoefficients = inputLinearCoefficients(matrix -> n - 1, column);
                        result = addLinearCombinationOfColumns(matrix, columnCoefficients, column);
                        notifyErrorMessage(result);
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
