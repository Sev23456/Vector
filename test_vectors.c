#include "vector_api.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

static void fill_int_values(Vector* vector, const int* values, size_t count) {
    size_t index;

    for (index = 0; index < count; ++index) {
        assert(vector_set(vector, index, &values[index]) == VECTOR_OK);
    }
}

static void fill_double_values(Vector* vector, const double* values, size_t count) {
    size_t index;

    for (index = 0; index < count; ++index) {
        assert(vector_set(vector, index, &values[index]) == VECTOR_OK);
    }
}

static void fill_complex_values(Vector* vector, const Complex* values, size_t count) {
    size_t index;

    for (index = 0; index < count; ++index) {
        assert(vector_set(vector, index, &values[index]) == VECTOR_OK);
    }
}

static void test_int_sum_and_dot(void) {
    const int lhs_values[] = {1, 2, 3, 4};
    const int rhs_values[] = {5, 6, 7, 8};
    Vector* lhs = vector_create(get_int_field_info(), 4);
    Vector* rhs = vector_create(get_int_field_info(), 4);
    Vector* sum = NULL;
    int dot = 0;
    int value = 0;

    assert(lhs != NULL);
    assert(rhs != NULL);

    fill_int_values(lhs, lhs_values, 4);
    fill_int_values(rhs, rhs_values, 4);

    assert(vector_sum(lhs, rhs, &sum) == VECTOR_OK);
    assert(sum != NULL);
    assert(vector_size(sum) == 4);
    assert(vector_field_info(sum) == get_int_field_info());

    assert(vector_get_copy(sum, 0, &value) == VECTOR_OK);
    assert(value == 6);
    assert(vector_get_copy(sum, 3, &value) == VECTOR_OK);
    assert(value == 12);

    assert(vector_dot(lhs, rhs, &dot) == VECTOR_OK);
    assert(dot == 70);

    vector_free(lhs);
    vector_free(rhs);
    vector_free(sum);
}

static void test_double_sum_and_dot(void) {
    const double lhs_values[] = {1.5, -2.0, 0.25};
    const double rhs_values[] = {2.0, 4.0, 8.0};
    Vector* lhs = vector_create(get_double_field_info(), 3);
    Vector* rhs = vector_create(get_double_field_info(), 3);
    Vector* sum = NULL;
    double dot = 0.0;
    double value = 0.0;

    assert(lhs != NULL);
    assert(rhs != NULL);

    fill_double_values(lhs, lhs_values, 3);
    fill_double_values(rhs, rhs_values, 3);

    assert(vector_sum(lhs, rhs, &sum) == VECTOR_OK);
    assert(sum != NULL);

    assert(vector_get_copy(sum, 0, &value) == VECTOR_OK);
    assert(fabs(value - 3.5) < 1e-9);
    assert(vector_get_copy(sum, 2, &value) == VECTOR_OK);
    assert(fabs(value - 8.25) < 1e-9);

    assert(vector_dot(lhs, rhs, &dot) == VECTOR_OK);
    assert(fabs(dot - (-3.0)) < 1e-9);

    vector_free(lhs);
    vector_free(rhs);
    vector_free(sum);
}

static void test_complex_sum_and_dot(void) {
    const Complex lhs_values[] = {
        {1.0, 2.0},
        {0.0, -1.0}
    };
    const Complex rhs_values[] = {
        {3.0, 4.0},
        {2.0, 5.0}
    };
    Vector* lhs = vector_create(get_complex_field_info(), 2);
    Vector* rhs = vector_create(get_complex_field_info(), 2);
    Vector* sum = NULL;
    Complex dot = {0.0, 0.0};
    Complex value = {0.0, 0.0};

    assert(lhs != NULL);
    assert(rhs != NULL);

    fill_complex_values(lhs, lhs_values, 2);
    fill_complex_values(rhs, rhs_values, 2);

    assert(vector_sum(lhs, rhs, &sum) == VECTOR_OK);
    assert(sum != NULL);

    assert(vector_get_copy(sum, 0, &value) == VECTOR_OK);
    assert(complex_equal(value, complex_make(4.0, 6.0), 1e-9));
    assert(vector_get_copy(sum, 1, &value) == VECTOR_OK);
    assert(complex_equal(value, complex_make(2.0, 4.0), 1e-9));

    assert(vector_dot(lhs, rhs, &dot) == VECTOR_OK);
    assert(complex_equal(dot, complex_make(0.0, 8.0), 1e-9));

    vector_free(lhs);
    vector_free(rhs);
    vector_free(sum);
}

static void test_empty_vectors(void) {
    Vector* lhs = vector_create(get_double_field_info(), 0);
    Vector* rhs = vector_create(get_double_field_info(), 0);
    Vector* sum = NULL;
    double dot = 123.0;

    assert(lhs != NULL);
    assert(rhs != NULL);

    assert(vector_sum(lhs, rhs, &sum) == VECTOR_OK);
    assert(sum != NULL);
    assert(vector_size(sum) == 0);

    assert(vector_dot(lhs, rhs, &dot) == VECTOR_OK);
    assert(dot == 0.0);

    vector_free(lhs);
    vector_free(rhs);
    vector_free(sum);
}

static void test_mismatch_errors(void) {
    Vector* int_vector = vector_create(get_int_field_info(), 1);
    Vector* double_vector = vector_create(get_double_field_info(), 1);
    Vector* short_vector = vector_create(get_int_field_info(), 2);
    Vector* result = NULL;
    int int_value = 7;
    double double_value = 7.5;
    int dot = 0;

    assert(int_vector != NULL);
    assert(double_vector != NULL);
    assert(short_vector != NULL);

    assert(vector_set(int_vector, 0, &int_value) == VECTOR_OK);
    assert(vector_set(double_vector, 0, &double_value) == VECTOR_OK);

    assert(vector_sum(int_vector, double_vector, &result) == VECTOR_ERROR_TYPE_MISMATCH);
    assert(result == NULL);
    assert(vector_dot(int_vector, double_vector, &dot) == VECTOR_ERROR_TYPE_MISMATCH);

    assert(vector_set(short_vector, 0, &int_value) == VECTOR_OK);
    assert(vector_set(short_vector, 1, &int_value) == VECTOR_OK);

    assert(vector_sum(int_vector, short_vector, &result) == VECTOR_ERROR_SIZE_MISMATCH);
    assert(vector_dot(int_vector, short_vector, &dot) == VECTOR_ERROR_SIZE_MISMATCH);

    vector_free(int_vector);
    vector_free(double_vector);
    vector_free(short_vector);
}

static void test_fixed_size_and_index_errors(void) {
    Vector* vector = vector_create(get_int_field_info(), 7);
    int values[] = {1, 2, 3, 4, 5, 6, 7};
    int value = 0;
    size_t index;

    assert(vector != NULL);

    for (index = 0; index < sizeof(values) / sizeof(values[0]); ++index) {
        assert(vector_set(vector, index, &values[index]) == VECTOR_OK);
    }

    assert(vector_size(vector) == 7);
    assert(vector_get_copy(vector, 6, &value) == VECTOR_OK);
    assert(value == 7);
    assert(vector_get(vector, 7) == NULL);
    assert(vector_get_copy(vector, 7, &value) == VECTOR_ERROR_INDEX_RANGE);
    assert(vector_set(vector, 7, &value) == VECTOR_ERROR_INDEX_RANGE);

    value = 42;
    assert(vector_set(vector, 3, &value) == VECTOR_OK);
    assert(vector_get_copy(vector, 3, &value) == VECTOR_OK);
    assert(value == 42);

    vector_free(vector);
}

int main(void) {
    test_int_sum_and_dot();
    test_double_sum_and_dot();
    test_complex_sum_and_dot();
    test_empty_vectors();
    test_mismatch_errors();
    test_fixed_size_and_index_errors();

    printf("All vector tests passed.\n");
    return 0;
}
