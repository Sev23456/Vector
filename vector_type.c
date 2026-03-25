#include "vector_type.h"

static void int_add_value(void *result, const void *left, const void *right) {
    *(int *)result = *(const int *)left + *(const int *)right;
}

static void int_subtract_value(void *result, const void *left, const void *right) {
    *(int *)result = *(const int *)left - *(const int *)right;
}

static void *int_create_zero_result(void) {
    int *result = malloc(sizeof(int));

    if (result) {
        *result = 0;
    }

    return result;
}

static void int_accumulate_dot(void *accumulator, const void *left, const void *right) {
    *(int *)accumulator += *(const int *)left * *(const int *)right;
}

static void int_print_value(const void *value) {
    printf("%d", *(const int *)value);
}

static void double_add_value(void *result, const void *left, const void *right) {
    *(double *)result = *(const double *)left + *(const double *)right;
}

static void double_subtract_value(void *result, const void *left, const void *right) {
    *(double *)result = *(const double *)left - *(const double *)right;
}

static void *double_create_zero_result(void) {
    double *result = malloc(sizeof(double));

    if (result) {
        *result = 0.0;
    }

    return result;
}

static void double_accumulate_dot(void *accumulator, const void *left, const void *right) {
    *(double *)accumulator += *(const double *)left * *(const double *)right;
}

static void double_print_value(const void *value) {
    printf("%.2f", *(const double *)value);
}

static void complex_add_value(void *result, const void *left, const void *right) {
    *(Complex *)result = Sum(*(const Complex *)left, *(const Complex *)right);
}

static void complex_subtract_value(void *result, const void *left, const void *right) {
    *(Complex *)result = Subtraction(*(const Complex *)left, *(const Complex *)right);
}

static void *complex_create_zero_result(void) {
    Complex *result = malloc(sizeof(Complex));

    if (result) {
        *result = (Complex){0.0, 0.0};
    }

    return result;
}

static void complex_accumulate_dot(void *accumulator, const void *left, const void *right) {
    Complex product = Product(*(const Complex *)left, *(const Complex *)right);
    *(Complex *)accumulator = Sum(*(Complex *)accumulator, product);
}

static void complex_print_value(const void *value) {
    Complex c = *(const Complex *)value;

    if (c.imag >= 0) {
        printf("%.2f+%.2fi", c.real, c.imag);
    } else {
        printf("%.2f%.2fi", c.real, c.imag);
    }
}

static const VectorOps INT_OPS = {
    sizeof(int),
    int_add_value,
    int_subtract_value,
    int_create_zero_result,
    int_accumulate_dot,
    int_print_value
};

static const VectorOps DOUBLE_OPS = {
    sizeof(double),
    double_add_value,
    double_subtract_value,
    double_create_zero_result,
    double_accumulate_dot,
    double_print_value
};

static const VectorOps COMPLEX_OPS = {
    sizeof(Complex),
    complex_add_value,
    complex_subtract_value,
    complex_create_zero_result,
    complex_accumulate_dot,
    complex_print_value
};

const VectorOps* get_vector_ops(NumericType type) {
    switch (type) {
        case TYPE_INT:
            return &INT_OPS;
        case TYPE_DOUBLE:
            return &DOUBLE_OPS;
        case TYPE_COMPLEX:
            return &COMPLEX_OPS;
        default:
            return NULL;
    }
}
