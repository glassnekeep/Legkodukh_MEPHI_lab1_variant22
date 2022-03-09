//
// Created by - on 09.03.2022.
//

#include "RingInfo.h"

size_t intSize = sizeof(int);

size_t doubleSize = sizeof(double);

size_t complexSize = sizeof(ComplexNumber);

int ringInfoEquals(RingInfo* ringInfo1, RingInfo* ringInfo2) {
    if (ringInfo1 -> size == ringInfo2 -> size
    && ringInfo1 -> zero == ringInfo2 -> zero
    && ringInfo1 -> one == ringInfo2 -> one
    && ringInfo1 -> sum == ringInfo2 -> sum
    && ringInfo1 -> opposite == ringInfo2 -> opposite
    && ringInfo1 -> multiply == ringInfo2 -> multiply) {
        return 1;
    } else {
        return 0;
    }
}

size_t getIntSize() {
    return sizeof(int);
}

size_t getDoubleSize() {
    return sizeof(double);
}

size_t getComplexSize() {
    return sizeof(ComplexNumber);
}

int* intZero;
int* intOne;

double* doubleZero;
double* doubleOne;

ComplexNumber* complexZero;
ComplexNumber* complexOne;

int* getIntZero() {
    if (!intZero) {
        intZero = malloc(sizeof(int));
        *intZero = 0;
    }
    return intZero;
}

double* getDoubleZero() {
    if (!doubleZero) {
        doubleZero = malloc(sizeof(double));
        *doubleZero = 0.0;
    }
    return doubleZero;
}

ComplexNumber* getComplexZero() {
    if (!complexZero) {
        complexZero = malloc(sizeof(ComplexNumber));
        complexZero -> realPart = 0.0;
        complexZero -> imaginaryPart = 0.0;
    }
    return complexZero;
}

int* getIntOne() {
    if (!intOne) {
        intOne = malloc(sizeof(int));
        *intOne = 1;
    }
    return intOne;
}

double* getDoubleOne() {
    if (!doubleOne) {
        doubleOne = malloc(sizeof(double));
        *doubleOne = 1.0;
    }
    return doubleOne;
}

ComplexNumber* getComplexOne() {
    if (!complexOne) {
        complexOne = malloc(sizeof(ComplexNumber));
        complexOne -> realPart = 1.0;
        complexOne -> imaginaryPart = 0.0;
    }
    return complexOne;
}

void* intSum(const void* value1, const void* value2) {
    int* result = malloc(sizeof(int));
    *result = *(int*)value1 + *(int*)value2;
    return result;
}

void* doubleSum(const void* value1, const void* value2) {
    double* result = malloc(sizeof(double));
    *result = *(double*)value1 + *(double*)value2;
    return result;
}

void* complexSum(const void* value1, const void* value2) {
    ComplexNumber* result = malloc(sizeof(ComplexNumber));
    result -> realPart = ((ComplexNumber*) value1) -> realPart + ((ComplexNumber*) value2) -> realPart;
    result -> imaginaryPart = ((ComplexNumber*) value1) -> imaginaryPart + ((ComplexNumber*) value2) -> imaginaryPart;
    return result;
}

void* oppositeInt(void* value) {
    int* opposite = malloc(sizeof(int));
    *opposite = (-1) * *(int*) value;
    return opposite;
}

void* oppositeDouble(void* value) {
    double* opposite = malloc(sizeof(double));
    *opposite = (-1.0) * *(double*) value;
    return opposite;
}

void* oppositeComplex(void* value) {
    ComplexNumber* opposite = malloc(sizeof(ComplexNumber));
    opposite -> realPart = ((ComplexNumber*) value) -> realPart * (-1.0);
    opposite -> imaginaryPart = ((ComplexNumber*) value) -> imaginaryPart * (-1.0);
    return opposite;
}

void* intMultiply(void* value1, void* value2) {
    int* result = malloc(sizeof(int));
    *result = *(int*) value1 * *(int*) value2;
    return result;
}

void* doubleMultiply(void* value1, void* value2) {
    double* result = malloc(sizeof(double));
    *result = *(double*) value1 * *(double*) value2;
    return result;
}

void* complexMultiply(void* value1, void* value2) {
    ComplexNumber* result = malloc(sizeof(ComplexNumber));
    double x1, x2, y1, y2;
    x1 = ((ComplexNumber*) value1) -> realPart;
    x2 = ((ComplexNumber*) value2) -> realPart;
    y1 = ((ComplexNumber*) value1) -> imaginaryPart;
    y2 = ((ComplexNumber*) value2) -> imaginaryPart;
    result -> realPart = x1 * x2 - y1 * y2;
    result -> imaginaryPart = x1 * y2 + x2 * y1;
    return result;
}

void* intMultiplyOnDouble(void* value, double number) {
    int* result = malloc(sizeof(int));
    *result = (int)round((*(int*) value) * number);
    return result;
}

void* doubleMultiplyOnDouble(void* value, double number) {
    double* result = malloc(sizeof(double));
    *result = number * *(double*) value;
    return result;
}

void* complexMultiplyOnDouble(void* value, double number) {
    ComplexNumber* result = malloc(sizeof(ComplexNumber));
    result -> realPart = ((ComplexNumber*) value) -> realPart * number;
    result -> imaginaryPart = ((ComplexNumber*) value) -> imaginaryPart * number;
    return result;
}

void createIntRingInfo(RingInfo* ringInfo) {
    ringInfo -> size = getIntSize();
    ringInfo -> zero = getIntZero();
    ringInfo -> one = getIntOne();
    ringInfo -> sum = intSum;
    ringInfo -> opposite = oppositeInt;
    ringInfo -> multiply = intMultiply;
    ringInfo -> multiplyOnDouble = intMultiplyOnDouble;
}

void createDoubleRingInfo(RingInfo* ringInfo) {
    ringInfo -> size = getDoubleSize();
    ringInfo -> zero = getDoubleZero();
    ringInfo -> one = getDoubleOne();
    ringInfo -> sum = doubleSum;
    ringInfo -> opposite = oppositeDouble;
    ringInfo -> multiply = doubleMultiply;
    ringInfo -> multiplyOnDouble = doubleMultiplyOnDouble;
}

void createComplexRingInfo(RingInfo* ringInfo) {
    ringInfo -> size = getComplexSize();
    ringInfo -> zero = getComplexZero();
    ringInfo -> one = getComplexOne();
    ringInfo -> sum = complexSum;
    ringInfo -> opposite = oppositeComplex;
    ringInfo -> multiply = complexMultiply;
    ringInfo -> multiplyOnDouble = complexMultiplyOnDouble;
}