#ifndef VECTOR_TYPE
#define VECTOR_TYPE

#include <stddef.h>
#include "complex.h"
#include "field_info.h"

typedef struct Vector {
    FieldInfo* fieldinfo;
    void* data;
    size_t size;
    size_t capacity;
} Vector;

Vector* vector_create(FieldInfo* fieldinfo);

void remove_data(Vector*);

void add_value(Vector*, void* value);

void change_value(Vector*, void* value);

void print_vector(Vector* vector);

void get_value(Vector* vector);

Vector* vector_Sum(Vector* vector_1, Vector* vector_2);

void scalar_product(Vector* vector_1, Vector* vector_2, void* result);

#endif