#ifndef N_VECTOR_H
#define N_VECTOR_H

#include "complex_ops.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_COMPLEX
} NumericType;

typedef struct VectorOps VectorOps;

typedef struct {
    NumericType type;
    int dimension;
    void *data;
    const VectorOps *ops;
} NVector;

#define GET_ELEM(vec, idx, type) (((type*)((vec)->data))[idx])
#define SET_ELEM(vec, idx, type, val) (((type*)((vec)->data))[idx] = (val))

NVector* create_vector(NumericType type, int dim, const void* values);
void free_vector(NVector* v);

NVector* add_vectors(NVector* a, NVector* b);
NVector* subtract_vectors(NVector* a, NVector* b);
void* dot_product(NVector* a, NVector* b);

void print_vector(NVector* v);
void print_scalar(NumericType type, const void* value);

#endif
