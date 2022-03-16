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
    system("clear");
    fflush(stdout);
}

double* inputLinearCoefficients(int number, int raw) {
    double* array = malloc(sizeof(double) * number);
    for (int i = 0; i < number; i++) {
        int currentRaw = i;
        if (i >= raw) {
            currentRaw++;
        }
        printf("Enter coefficient for line %d\n", currentRaw);
        double newValue = 0.0;
        while (scanf("%lf", &newValue) != 1) {
            printf("Wrong type, double required\n");
            getchar();
        }
        array[i] = newValue;
    }
    return array;
}

int main() {
    Matrix* matrix = NULL;
    RingInfo* ringInfo = malloc(sizeof(RingInfo));
    int choice = 0;
    int dataType = 0;
    int m = 0;
    int n = 0;
    do {
        printf("1. Form matrix\n2. Export matrix\n3. Operations\n4. Print tests\n5. Clear screen\n6. Exit\n");
        while (scanf("%d", &choice) != 1 || ((int) choice > 6) || (int) choice < 1) {
            printf("Error. Enter correct number\n");
            getchar();
        }
        switch (choice) {
            case 1:
                printf("Enter data type, where:\n1 - integer\n2 - double\n3 - complex\n");
                while ((scanf("%d", &dataType) != 1) || ((int) dataType > 3) || (int) dataType < 1) {
                    printf("Error. Enter correct number");
                    getchar();
                }
                int choice1 = 0;
                printf("1. Read from keyboard\n2. Random value\n");
                while (scanf("%d", &choice1) != 1 || ((int) choice1 > 2) || (int) choice1 < 1) {
                    printf("Error. Enter correct number\n");
                    getchar();
                }
                //TODO тут надо разобраться с инпутами и когда мы вообще создаем матрицу
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
                if (matrix != NULL) {
                    freeMatrix(matrix);
                }
                switch (choice1) {
                    case 1:
                        printf("Enter number of lines\n");
                        while (scanf("%d", &m) != 1) {
                            printf("Error. Enter correct number of lines\n");
                            getchar();
                        }
                        printf("Enter number of columns\n");
                        while (scanf("%d", &n) != 1) {
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
                printf("");
                int index;
                printf("1. Sum two matrices\n2. Multiply two matrices\n3. Transpose the matrix\n4. Add linear combination of lines\n5. Add linear combination of columns\n");
                while (scanf("%d", &choice1) != 1 || ((int) choice1 > 5) || (int) choice1 < 1) {
                    printf("Error. Enter correct number\n");
                    getchar();
                }
                printf("current matrix is %d x %d\n", matrix -> m, matrix -> n);
                switch (choice1) {
                    case 1:
                        Matrix* sumMatrix = inputMatrix(matrix -> m, matrix -> n, dataType);
                        matrix = matrixSum(matrix, sumMatrix);
                        freeMatrix((sumMatrix));
                        break;
                    case 2:
                        //TODO разобраться с ограничениями на ввод
                        int newMatrixNumberOfColumns;
                        printf("Enter number of columns in the second matrix\n");
                        while (scanf("%d", &newMatrixNumberOfColumns) != 1 || newMatrixNumberOfColumns < 1) {
                            printf("Wrong number of columns. Enter it again\n");
                        }
                        Matrix* multiplyMatrix = inputMatrix(matrix -> n, newMatrixNumberOfColumns, dataType);
                        matrix = matrixMultiply(matrix, multiplyMatrix);
                        freeMatrix(multiplyMatrix);
                        break;
                    case 3:
                        matrix = transpose(matrix);
                        break;
                    case 4:
                        int line = 0;
                        while (scanf("%d", &line) != 1 || line < 0) {
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
                break;
            case 5:
                clearScreen();
                break;
            default:
                exit(0);
                break;
        }
    } while (choice != 5);
    return 0;
}
