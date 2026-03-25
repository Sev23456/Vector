#include "n_vector.h"

#include "vector_type.h"

#include <stdint.h>

typedef void (*BinaryValueOp)(void *result, const void *left, const void *right);

static int vectors_are_compatible(const NVector *a, const NVector *b) {
    return a && b &&
        a->ops && b->ops &&
        a->type == b->type &&
        a->ops == b->ops &&
        a->dimension == b->dimension &&
        a->dimension > 0;
}

static unsigned char *get_element_ptr(NVector *vector, int index) {
    return (unsigned char *)vector->data + ((size_t)index * vector->ops->element_size);
}

static const unsigned char *get_const_element_ptr(const NVector *vector, int index) {
    return (const unsigned char *)vector->data + ((size_t)index * vector->ops->element_size);
}

static NVector* apply_binary_vector_op(NVector *a, NVector *b, BinaryValueOp op) {
    NVector *result;

    if (!vectors_are_compatible(a, b) || !op) {
        return NULL;
    }

    result = create_vector(a->type, a->dimension, NULL);
    if (!result) {
        return NULL;
    }

    for (int i = 0; i < a->dimension; i++) {
        op(get_element_ptr(result, i), get_const_element_ptr(a, i), get_const_element_ptr(b, i));
    }

    return result;
}

NVector* create_vector(NumericType type, int dim, const void* values) {
    NVector *v;
    const VectorOps *ops = get_vector_ops(type);
    size_t data_size;

    if (dim <= 0 || !ops) {
        return NULL;
    }

    if ((size_t)dim > SIZE_MAX / ops->element_size) {
        return NULL;
    }

    v = malloc(sizeof(NVector));
    if (!v) {
        return NULL;
    }

    data_size = (size_t)dim * ops->element_size;
    v->type = type;
    v->dimension = dim;
    v->ops = ops;
    v->data = malloc(data_size);
    if (!v->data) {
        free(v);
        return NULL;
    }

    if (values) {
        memcpy(v->data, values, data_size);
    } else {
        memset(v->data, 0, data_size);
    }

    return v;
}

void free_vector(NVector* v) {
    if (v) {
        if (v->data) {
            free(v->data);
        }
        free(v);
    }
}

NVector* add_vectors(NVector* a, NVector* b) {
    return apply_binary_vector_op(a, b, (a && a->ops) ? a->ops->add_value : NULL);
}

NVector* subtract_vectors(NVector* a, NVector* b) {
    return apply_binary_vector_op(a, b, (a && a->ops) ? a->ops->subtract_value : NULL);
}

void* dot_product(NVector* a, NVector* b) {
    void *result;

    if (!vectors_are_compatible(a, b)) {
        return NULL;
    }

    result = a->ops->create_zero_result();
    if (!result) {
        return NULL;
    }

    for (int i = 0; i < a->dimension; i++) {
        a->ops->accumulate_dot(result, get_const_element_ptr(a, i), get_const_element_ptr(b, i));
    }

    return result;
}

void print_vector(NVector* v) {
    if (!v) {
        printf("NULL vector\n");
        return;
    }

    if (!v->ops) {
        printf("Invalid vector\n");
        return;
    }

    printf("[");
    for (int i = 0; i < v->dimension; i++) {
        if (i > 0) {
            printf(", ");
        }
        v->ops->print_value(get_const_element_ptr(v, i));
    }
    printf("]\n");
}

void print_scalar(NumericType type, const void* value) {
    const VectorOps *ops;

    if (!value) {
        printf("NULL");
        return;
    }

    ops = get_vector_ops(type);
    if (!ops) {
        printf("Invalid scalar");
        return;
    }

    ops->print_value(value);
}
