#include "n_vector.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EXPECT_INT_EQ(a,b) do { if ((a) != (b)) { fprintf(stderr, "FAIL %s:%d: %d != %d\n", __FILE__, __LINE__, (a), (b)); return 1; } } while(0)
#define EXPECT_DOUBLE_NEAR(a,b,eps) do { if (fabs((a)-(b)) > (eps)) { fprintf(stderr, "FAIL %s:%d: %f != %f\n", __FILE__, __LINE__, (a), (b)); return 1; } } while(0)

int test_int_add_dot() {
    int a_vals[] = {1,2,3};
    int b_vals[] = {4,5,6};
    NVector* a = create_vector(TYPE_INT, 3, a_vals);
    NVector* b = create_vector(TYPE_INT, 3, b_vals);

    if (!a || !b || !a->ops || !b->ops || a->ops != b->ops) return 1;

    NVector* s = add_vectors(a,b);
    if (!s) return 1;
    EXPECT_INT_EQ(GET_ELEM(s,0,int), 5);
    EXPECT_INT_EQ(GET_ELEM(s,1,int), 7);
    EXPECT_INT_EQ(GET_ELEM(s,2,int), 9);

    int* dp = (int*)dot_product(a,b);
    if (!dp) return 1;
    EXPECT_INT_EQ(*dp, 32);

    free(dp);
    free_vector(a);
    free_vector(b);
    free_vector(s);
    return 0;
}

int test_type_mismatch() {
    int i_vals[] = {1,2,3};
    double d_vals[] = {1.0,2.0,3.0};
    NVector* vi = create_vector(TYPE_INT, 3, i_vals);
    NVector* vd = create_vector(TYPE_DOUBLE, 3, d_vals);

    if (!vi || !vd || !vi->ops || !vd->ops || vi->ops == vd->ops) return 1;

    NVector* s = add_vectors(vi, vd);
    if (s) return 1;

    void* dp = dot_product(vi, vd);
    if (dp) return 1;

    free_vector(vi);
    free_vector(vd);
    return 0;
}

int test_double_near() {
    double a_vals[] = {1.5,2.5};
    double b_vals[] = {0.5,1.5};
    NVector* a = create_vector(TYPE_DOUBLE, 2, a_vals);
    NVector* b = create_vector(TYPE_DOUBLE, 2, b_vals);

    NVector* s = add_vectors(a,b);
    if (!s) return 1;
    EXPECT_DOUBLE_NEAR(GET_ELEM(s,0,double), 2.0, 1e-6);
    EXPECT_DOUBLE_NEAR(GET_ELEM(s,1,double), 4.0, 1e-6);

    double* dp = (double*)dot_product(a,b);
    if (!dp) return 1;
    EXPECT_DOUBLE_NEAR(*dp, 4.5, 1e-6);

    free(dp);
    free_vector(a);
    free_vector(b);
    free_vector(s);
    return 0;
}

int test_invalid_dimension() {
    if (create_vector(TYPE_INT, 0, NULL) != NULL) return 1;
    if (create_vector(TYPE_DOUBLE, -1, NULL) != NULL) return 1;
    if (create_vector(TYPE_COMPLEX, 0, NULL) != NULL) return 1;
    return 0;
}

int main(void) {
    printf("Running compact unit tests...\n");
    if (test_int_add_dot() != 0) { fprintf(stderr, "test_int_add_dot failed\n"); return 1; }
    if (test_type_mismatch() != 0) { fprintf(stderr, "test_type_mismatch failed\n"); return 1; }
    if (test_double_near() != 0) { fprintf(stderr, "test_double_near failed\n"); return 1; }
    if (test_invalid_dimension() != 0) { fprintf(stderr, "test_invalid_dimension failed\n"); return 1; }
    printf("All compact unit tests passed.\n");
    return 0;
}
