#ifndef VECTOR_API_H
#define VECTOR_API_H

#include <stddef.h>

typedef struct Vector {
    size_t size;
    double* data;
} Vector;

Vector* vector_create(size_t n);
void vector_free(Vector* v);
int vector_set(Vector* v, size_t idx, double val);
double vector_get(const Vector* v, size_t idx);
Vector* vector_add(const Vector* a, const Vector* b);
double vector_dot(const Vector* a, const Vector* b, int* err);
void vector_print(const Vector* v);

#endif // VECTOR_API_H
