#include "n_vector.h"
#include <assert.h>
#include <math.h>

void test_create_and_print() {
    printf("Testing vector creation and printing...\n");

    int int_vals[] = {1, 2, 3, 4, 5};
    NVector* v1 = create_vector(TYPE_INT, 5, int_vals);
    assert(v1 != NULL);
    assert(v1->type == TYPE_INT);
    assert(v1->dimension == 5);
    printf("Integer vector: ");
    print_vector(v1);

    double double_vals[] = {1.5, 2.5, 3.5};
    NVector* v2 = create_vector(TYPE_DOUBLE, 3, double_vals);
    assert(v2 != NULL);
    assert(v2->type == TYPE_DOUBLE);
    assert(v2->dimension == 3);
    printf("Double vector: ");
    print_vector(v2);

    Complex complex_vals[] = {{1.0, 2.0}, {3.0, -1.0}, {0.0, 5.0}};
    NVector* v3 = create_vector(TYPE_COMPLEX, 3, complex_vals);
    assert(v3 != NULL);
    assert(v3->type == TYPE_COMPLEX);
    assert(v3->dimension == 3);
    printf("Complex vector: ");
    print_vector(v3);

    free_vector(v1);
    free_vector(v2);
    free_vector(v3);

    printf("Create and print tests passed!\n\n");
}

void test_addition() {
    printf("Testing vector addition...\n");

    int vals1[] = {1, 2, 3};
    int vals2[] = {4, 5, 6};
    NVector* v1 = create_vector(TYPE_INT, 3, vals1);
    NVector* v2 = create_vector(TYPE_INT, 3, vals2);
    NVector* sum = add_vectors(v1, v2);
    assert(sum != NULL);
    assert(GET_ELEM(sum, 0, int) == 5);
    assert(GET_ELEM(sum, 1, int) == 7);
    assert(GET_ELEM(sum, 2, int) == 9);
    printf("Integer vector addition: ");
    print_vector(v1);
    printf(" + ");
    print_vector(v2);
    printf(" = ");
    print_vector(sum);

    free_vector(v1);
    free_vector(v2);
    free_vector(sum);

    double dvals1[] = {1.5, 2.5, 3.5};
    double dvals2[] = {0.5, 1.5, 2.5};
    NVector* dv1 = create_vector(TYPE_DOUBLE, 3, dvals1);
    NVector* dv2 = create_vector(TYPE_DOUBLE, 3, dvals2);
    NVector* dsum = add_vectors(dv1, dv2);
    assert(dsum != NULL);
    assert(fabs(GET_ELEM(dsum, 0, double) - 2.0) < 0.01);
    assert(fabs(GET_ELEM(dsum, 1, double) - 4.0) < 0.01);
    assert(fabs(GET_ELEM(dsum, 2, double) - 6.0) < 0.01);
    printf("Double vector addition: ");
    print_vector(dv1);
    printf(" + ");
    print_vector(dv2);
    printf(" = ");
    print_vector(dsum);

    free_vector(dv1);
    free_vector(dv2);
    free_vector(dsum);

    printf("Addition tests passed!\n\n");
}

void test_subtraction() {
    printf("Testing vector subtraction...\n");

    int vals1[] = {5, 7, 9};
    int vals2[] = {2, 3, 4};
    NVector* v1 = create_vector(TYPE_INT, 3, vals1);
    NVector* v2 = create_vector(TYPE_INT, 3, vals2);
    NVector* diff = subtract_vectors(v1, v2);
    assert(diff != NULL);
    assert(GET_ELEM(diff, 0, int) == 3);
    assert(GET_ELEM(diff, 1, int) == 4);
    assert(GET_ELEM(diff, 2, int) == 5);
    printf("Integer vector subtraction: ");
    print_vector(v1);
    printf(" - ");
    print_vector(v2);
    printf(" = ");
    print_vector(diff);

    free_vector(v1);
    free_vector(v2);
    free_vector(diff);

    printf("Subtraction tests passed!\n\n");
}

void test_dot_product() {
    printf("Testing dot product...\n");

    int vals1[] = {1, 2, 3};
    int vals2[] = {4, 5, 6};
    NVector* v1 = create_vector(TYPE_INT, 3, vals1);
    NVector* v2 = create_vector(TYPE_INT, 3, vals2);
    int* dp_int = (int*)dot_product(v1, v2);
    assert(dp_int != NULL);
    assert(*dp_int == 32);
    printf("Integer vector dot product: ");
    print_vector(v1);
    printf(" · ");
    print_vector(v2);
    printf(" = %d\n", *dp_int);

    free(dp_int);
    free_vector(v1);
    free_vector(v2);

    double dvals1[] = {1.0, 2.0, 3.0};
    double dvals2[] = {0.5, 1.5, 2.5};
    NVector* dv1 = create_vector(TYPE_DOUBLE, 3, dvals1);
    NVector* dv2 = create_vector(TYPE_DOUBLE, 3, dvals2);
    double* dp_double = (double*)dot_product(dv1, dv2);
    assert(dp_double != NULL);
    assert(fabs(*dp_double - 11.0) < 0.01);
    printf("Double vector dot product: ");
    print_vector(dv1);
    printf(" · ");
    print_vector(dv2);
    printf(" = %.2f\n", *dp_double);

    free(dp_double);
    free_vector(dv1);
    free_vector(dv2);

    Complex cvals1[] = {{1.0, 0.0}, {0.0, 1.0}};
    Complex cvals2[] = {{1.0, 0.0}, {0.0, -1.0}};
    NVector* cv1 = create_vector(TYPE_COMPLEX, 2, cvals1);
    NVector* cv2 = create_vector(TYPE_COMPLEX, 2, cvals2);
    Complex* dp_complex = (Complex*)dot_product(cv1, cv2);
    assert(dp_complex != NULL);
    assert(fabs(dp_complex->real - 2.0) < 0.01);
    assert(fabs(dp_complex->imag) < 0.01);
    printf("Complex vector dot product: ");
    print_vector(cv1);
    printf(" · ");
    print_vector(cv2);
    printf(" = %.2f+%.2fi\n", dp_complex->real, dp_complex->imag);

    free(dp_complex);
    free_vector(cv1);
    free_vector(cv2);

    printf("Dot product tests passed!\n\n");
}

void test_edge_cases() {
    printf("Testing edge cases...\n");

    int int_vals[] = {1, 2, 3};
    double double_vals[] = {1.0, 2.0, 3.0};
    NVector* v_int = create_vector(TYPE_INT, 3, int_vals);
    NVector* v_double = create_vector(TYPE_DOUBLE, 3, double_vals);

    NVector* sum = add_vectors(v_int, v_double);
    assert(sum == NULL);

    void* dp = dot_product(v_int, v_double);
    assert(dp == NULL);

    int small_vals[] = {1, 2};
    NVector* v_small = create_vector(TYPE_INT, 2, small_vals);
    sum = add_vectors(v_int, v_small);
    assert(sum == NULL);

    dp = dot_product(v_int, v_small);
    assert(dp == NULL);

    free_vector(v_int);
    free_vector(v_double);
    free_vector(v_small);

    printf("Edge case tests passed!\n\n");
}

int main(void) {
    printf("Running N-Dimensional Vector Tests...\n\n");

    test_create_and_print();
    test_addition();
    test_subtraction();
    test_dot_product();
    test_edge_cases();

    printf("All tests passed successfully!\n");

    return 0;
}
