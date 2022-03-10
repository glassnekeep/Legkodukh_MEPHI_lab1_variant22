#include <stdio.h>
#include "Matrix.h"

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

int main() {
    Matrix* matrix;
    RingInfo* ringInfo = malloc(sizeof(RingInfo));
    int m = 0;
    int n = 0;
    int choice = 0;
    int dataType = 0;
    do {
        printf("1. Form matrix\n2. Export matrix\n3. Operations\n4. Clear screen\n5. Exit");
        while (scanf("%d", &choice) != 1 || ((int) choice > 5) || (int) choice < 1) {
            printf("Error. Enter correct number\n");
            getchar();
        }
        switch (choice) {
            int choice1 = 0;
            case 1:
                printf("Enter data type, where:\n1 - integer\n2 - double\n3 - complex");
                while ((scanf("%d", &dataType) != 1) || ((int) dataType > 3) || (int) dataType < 1) {
                    printf("Error. Enter correct number");
                }
                printf("1. Read from keyboard\n2. Read from binary file\n3. Random value\n");
                while (scanf("%d", &choice1) != 1 || ((int) choice1 > 3) || (int) choice1 < 1) {
                    printf("Error. Enter correct number\n");
                    getchar();
                }
                switch (dataType) {
                    case 1:
                        createIntRingInfo(ringInfo);
                        matrix = intInput(m, n, ringInfo);
                        break;
                    case 2:
                        createDoubleRingInfo(ringInfo);
                        matrix = doubleInput(m, n, ringInfo);
                        break;
                    case 3:
                        createComplexRingInfo(ringInfo);
                        matrix = complexInput(m, n, ringInfo);
                        break;
                    default:
                        break;
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
                        break;
                    case 2:
                        printf("");
                        FILE *fl;
                        char* file;
                        scanf("%s", file);
                        fl = fopen(file, "rb");
                        if (fl) {
                            fread(&m, sizeof(int), 1, fl);
                            fread(&n, sizeof(int), 1, fl);
                            printf("m = %d, n = %d\n", m, n);
                            fread(string, sizeof(char) * 16, 1, fl);
                            fclose(fl);
                        } else {
                            printf("This file does not exist\n");
                        }
                        break;
                    case 3:
                        srand(time(NULL));
                        n = 1 + rand() % 10;
                        m = 1 + rand() % 10;
                        int stringSize = rand() % 40;
                        string = (char *) malloc(sizeof(char) * stringSize);
                        for (int i = 0; i < stringSize; i++) {
                            string[i] = (char) ('0' + rand() % 2);
                        }
                        break;
                }
                matrix = (int **) calloc(m, sizeof(int *));
                for (int i = 0; i < m; i++) {
                    matrix[i] = (int *) calloc(n, sizeof(int));
                }
                matrix = makeMatrixWithKnownBinaryStringAndDimension(string, m, n);
                //free(string);
                break;
            case 2:
                printf("1. Write matrix to console\n2. Write matrix to binary file\n");
                while (scanf("%d", &choice1) != 1 || ((int) choice1 > 2) || (int) choice1 < 1) {
                    printf("Error. Enter correct number\n");
                    getchar();
                }
                switch (choice1) {
                    case 1:
                        printMatrix(matrix, m, n);
                        break;
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
                }
                break;
            case 3:
                printf("");
                int index;
                printf("1. Insert a line by index\n2. Insert a column by index\n3. Delete a line by index\n4. Delete a column by index\n");
                while (scanf("%d", &choice1) != 1 || ((int) choice1 > 4) || (int) choice1 < 1) {
                    printf("Error. Enter correct number\n");
                    getchar();
                }
                printf("current matrix is %d x %d\n", m, n);
                printf("Please enter the index\n");
                switch (choice1) {
                    case 1:
                        while (scanf("%d", &index) != 1 || ((int) index >= m) || (int) index < 0) {
                            printf("Error. Enter correct index\n");
                            getchar();
                        }
                        int *line = calloc(n, sizeof(int));
                        printf("Enter %d numbers\n", n);
                        for (int i = 0; i < n; i++) {
                            scanf("%d", &line[i]);
                        }
                        matrix = insertRawByIndex(matrix, line, index, m, n);
                        m++;
                        break;
                    case 2:
                        while (scanf("%d", &index) != 1 || ((int) index >= n) || (int) index < 0) {
                            printf("Error. Enter correct index\n");
                            getchar();
                        }
                        int *column = calloc(m, sizeof(int));
                        printf("Enter %d numbers\n", m);
                        for (int i = 0; i < m; i++) {
                            scanf("%d", &column[i]);
                        }
                        matrix = insertColumnByIndex(matrix, column, index, m, n);
                        n++;
                        break;
                    case 3:
                        while (scanf("%d", &index) != 1 || ((int) index >= m) || (int) index < 0) {
                            printf("Error. Enter correct index\n");
                            getchar();
                        }
                        matrix = deleterRawByIndex(matrix, index, m, n);
                        m--;
                        break;
                    case 4:
                        while (scanf("%d", &index) != 1 || ((int) index >= n) || (int) index < 0) {
                            printf("Error. Enter correct index\n");
                            getchar();
                        }
                        matrix = deleteColumnByIndex(matrix, index, m, n);
                        n--;
                        break;
                }
                break;
            case 4:
                clearScreen();
                break;
            default:
                exit(0);
                break;
        }
    } while (choice != 4);
    return 0;
}
