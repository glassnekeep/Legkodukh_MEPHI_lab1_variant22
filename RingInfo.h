//
// Created by - on 09.03.2022.
//

#ifndef LEGKODUKH_MEPHI_LAB1_VARIANT22_RINGINFO_H
#define LEGKODUKH_MEPHI_LAB1_VARIANT22_RINGINFO_H

#include <stdlib.h>
#include <math.h>

typedef struct RingInfo {
    size_t size;
    void* zero;
    void* one;
    void* (*sum) (const void*, const void*);
    void* (*opposite) (void*);
    void* (*multiply) (void*, void*);
    void* (*multiplyOnDouble) (void*, double)
} RingInfo;

typedef struct ComplexNumber {
    double realPart;
    double imaginaryPart;
} ComplexNumber;

int ringInfoEquals(RingInfo* ringInfo1, RingInfo* ringInfo2);

size_t getIntSize();

size_t getDoubleSize();

size_t getComplexSize();

int* getIntZero();

double* getDoubleZero();

ComplexNumber* getComplexZero();

int* getIntOne();

double* getDoubleOne();

ComplexNumber* getComplexOne();

void* intSum(const void* value1, const void* value2);

void* doubleSum(const void* value1, const void* value2);

void* complexSum(const void* value1, const void* value2);

void* oppositeInt(void* value);

void* oppositeDouble(void* value);

void* oppositeComplex(void* value);

void* intMultiply(void* value1, void* value2);

void* doubleMultiply(void* value1, void* value2);

void* complexMultiply(void* value1, void* value2);

void* intMultiplyOnDouble(void* value, double number);

void* doubleMultiplyOnDouble(void* value, double number);

void* complexMultiplyOnDouble(void* value, double number);

void createIntRingInfo(RingInfo* ringInfo);

void createDoubleRingInfo(RingInfo* ringInfo);

void createComplexRingInfo(RingInfo* ringInfo);

#endif //LEGKODUKH_MEPHI_LAB1_VARIANT22_RINGINFO_H
