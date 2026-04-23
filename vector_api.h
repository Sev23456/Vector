#ifndef VECTOR_API_H
#define VECTOR_API_H

#include <stddef.h>

#include "field_info.h"

typedef enum VectorStatus {
    VECTOR_OK = 0,
    VECTOR_ERROR_NULL,
    VECTOR_ERROR_ALLOCATION,
    VECTOR_ERROR_INDEX_RANGE,
    VECTOR_ERROR_TYPE_MISMATCH,
    VECTOR_ERROR_SIZE_MISMATCH,
    VECTOR_ERROR_INVALID_FIELD
} VectorStatus;

typedef struct Vector Vector;

Vector* vector_create(const FieldInfo* field_info, size_t size);
void vector_free(Vector* vector);

size_t vector_size(const Vector* vector);
const FieldInfo* vector_field_info(const Vector* vector);

VectorStatus vector_set(Vector* vector, size_t index, const void* elem);
const void* vector_get(const Vector* vector, size_t index);
VectorStatus vector_get_copy(const Vector* vector, size_t index, void* out_elem);

VectorStatus vector_sum(const Vector* lhs, const Vector* rhs, Vector** out_result);
VectorStatus vector_dot(const Vector* lhs, const Vector* rhs, void* out_result);

void vector_print(const Vector* vector);
const char* vector_status_message(VectorStatus status);

#endif
