#include "vector_api.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Vector {
    unsigned char* data;
    size_t size;
    const FieldInfo* field_info;
};

static int field_info_is_valid(const FieldInfo* field_info) {
    return field_info != NULL &&
           field_info->elem_size > 0 &&
           field_info->print != NULL &&
           field_info->add != NULL &&
           field_info->multiply != NULL &&
           field_info->zero != NULL;
}

static void* vector_at(Vector* vector, size_t index) {
    return vector->data + index * vector->field_info->elem_size;
}

static const void* vector_at_const(const Vector* vector, size_t index) {
    return vector->data + index * vector->field_info->elem_size;
}

Vector* vector_create(const FieldInfo* field_info, size_t size) {
    Vector* vector;
    size_t index;

    if (!field_info_is_valid(field_info)) {
        return NULL;
    }
    if (field_info->elem_size != 0 && size > ((size_t)-1) / field_info->elem_size) {
        return NULL;
    }

    vector = (Vector*)malloc(sizeof(*vector));
    if (vector == NULL) {
        return NULL;
    }

    vector->data = NULL;
    vector->size = size;
    vector->field_info = field_info;

    if (size > 0) {
        vector->data = (unsigned char*)malloc(size * field_info->elem_size);
        if (vector->data == NULL) {
            free(vector);
            return NULL;
        }

        for (index = 0; index < size; ++index) {
            field_info->zero(vector_at(vector, index));
        }
    }

    return vector;
}

void vector_free(Vector* vector) {
    if (vector == NULL) {
        return;
    }

    free(vector->data);
    free(vector);
}

size_t vector_size(const Vector* vector) {
    if (vector == NULL) {
        return 0;
    }

    return vector->size;
}

const FieldInfo* vector_field_info(const Vector* vector) {
    if (vector == NULL) {
        return NULL;
    }

    return vector->field_info;
}

VectorStatus vector_set(Vector* vector, size_t index, const void* elem) {
    if (vector == NULL || elem == NULL) {
        return VECTOR_ERROR_NULL;
    }
    if (index >= vector->size) {
        return VECTOR_ERROR_INDEX_RANGE;
    }

    memcpy(vector_at(vector, index), elem, vector->field_info->elem_size);
    return VECTOR_OK;
}

const void* vector_get(const Vector* vector, size_t index) {
    if (vector == NULL || index >= vector->size) {
        return NULL;
    }

    return vector_at_const(vector, index);
}

VectorStatus vector_get_copy(const Vector* vector, size_t index, void* out_elem) {
    if (vector == NULL || out_elem == NULL) {
        return VECTOR_ERROR_NULL;
    }
    if (index >= vector->size) {
        return VECTOR_ERROR_INDEX_RANGE;
    }

    memcpy(out_elem, vector_at_const(vector, index), vector->field_info->elem_size);
    return VECTOR_OK;
}

VectorStatus vector_sum(const Vector* lhs, const Vector* rhs, Vector** out_result) {
    Vector* result;
    size_t index;

    if (out_result == NULL) {
        return VECTOR_ERROR_NULL;
    }
    *out_result = NULL;

    if (lhs == NULL || rhs == NULL) {
        return VECTOR_ERROR_NULL;
    }
    if (lhs->field_info != rhs->field_info) {
        return VECTOR_ERROR_TYPE_MISMATCH;
    }
    if (lhs->size != rhs->size) {
        return VECTOR_ERROR_SIZE_MISMATCH;
    }

    result = vector_create(lhs->field_info, lhs->size);
    if (result == NULL) {
        return VECTOR_ERROR_ALLOCATION;
    }

    for (index = 0; index < lhs->size; ++index) {
        lhs->field_info->add(
            vector_at_const(lhs, index),
            vector_at_const(rhs, index),
            vector_at(result, index)
        );
    }

    *out_result = result;
    return VECTOR_OK;
}

VectorStatus vector_dot(const Vector* lhs, const Vector* rhs, void* out_result) {
    void* product;
    size_t index;

    if (lhs == NULL || rhs == NULL || out_result == NULL) {
        return VECTOR_ERROR_NULL;
    }
    if (lhs->field_info != rhs->field_info) {
        return VECTOR_ERROR_TYPE_MISMATCH;
    }
    if (lhs->size != rhs->size) {
        return VECTOR_ERROR_SIZE_MISMATCH;
    }

    lhs->field_info->zero(out_result);
    product = malloc(lhs->field_info->elem_size);
    if (product == NULL) {
        return VECTOR_ERROR_ALLOCATION;
    }

    for (index = 0; index < lhs->size; ++index) {
        lhs->field_info->multiply(
            vector_at_const(lhs, index),
            vector_at_const(rhs, index),
            product
        );
        lhs->field_info->add(out_result, product, out_result);
    }

    free(product);
    return VECTOR_OK;
}

void vector_print(const Vector* vector) {
    size_t index;

    if (vector == NULL) {
        printf("(null)");
        return;
    }

    printf("[");
    for (index = 0; index < vector->size; ++index) {
        if (index > 0) {
            printf(", ");
        }
        vector->field_info->print(vector_at_const(vector, index));
    }
    printf("]");
}

const char* vector_status_message(VectorStatus status) {
    switch (status) {
        case VECTOR_OK:
            return "ok";
        case VECTOR_ERROR_NULL:
            return "null argument";
        case VECTOR_ERROR_ALLOCATION:
            return "allocation failed";
        case VECTOR_ERROR_INDEX_RANGE:
            return "index out of range";
        case VECTOR_ERROR_TYPE_MISMATCH:
            return "vectors store different element types";
        case VECTOR_ERROR_SIZE_MISMATCH:
            return "vectors have different sizes";
        case VECTOR_ERROR_INVALID_FIELD:
            return "invalid field description";
        default:
            return "unknown error";
    }
}
