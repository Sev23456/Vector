#include "math.h"

void* sum(void* a, void* b, void* result, DataType type) {
    switch (type) {
        case TYPE_INT: {
            int* res = (int*)result;
            *res = *(int*)a + *(int*)b;
            return res;
        }
        case TYPE_DOUBLE: {
            double* res = (double*)result;
            *res = *(double*)a + *(double*)b;
            return res;
        }
        case TYPE_COMPLEX: {
            Complex* res = (Complex*)result;
            res->real = ((Complex*)a)->real + ((Complex*)b)->real;
            res->imag = ((Complex*)a)->imag + ((Complex*)b)->imag;
            return res;
        }
        default:
            return NULL;
    }
}

// Универсальная функция умножения
void* multiply(void* a, void* b, void* result, DataType type) {
    if (!a || !b || !result) return NULL;
    
    switch (type) {
        case TYPE_INT: {
            int* res = (int*)result;
            *res = *(int*)a * *(int*)b;
            return res;
        }
        case TYPE_DOUBLE: {
            double* res = (double*)result;
            *res = *(double*)a * *(double*)b;
            return res;
        }
        case TYPE_COMPLEX: {
            Complex* ra = (Complex*)a;
            Complex* rb = (Complex*)b;
            Complex* res = (Complex*)result;
            
            // (a+bi)(c+di) = (ac-bd) + (ad+bc)i
            res->real = ra->real * rb->real - ra->imag * rb->imag;
            res->imag = ra->real * rb->imag + ra->imag * rb->real;
            return res;
        }
        default:
            return NULL;
    }
}