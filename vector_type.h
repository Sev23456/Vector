#ifndef VECTOR_TYPE_H
#define VECTOR_TYPE_H

#include "n_vector.h"

struct VectorOps {
    size_t element_size;
    void (*add_value)(void *result, const void *left, const void *right);
    void (*subtract_value)(void *result, const void *left, const void *right);
    void *(*create_zero_result)(void);
    void (*accumulate_dot)(void *accumulator, const void *left, const void *right);
    void (*print_value)(const void *value);
};

const VectorOps* get_vector_ops(NumericType type);

#endif
