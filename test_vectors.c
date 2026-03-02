#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vector_api.h"
#include <math.h>

static void test_add_and_dot_basic() {
    Vector* a = vector_create(3);
    Vector* b = vector_create(3);
    assert(a && b);
    vector_set(a,0,1.0); vector_set(a,1,2.0); vector_set(a,2,3.0);
    vector_set(b,0,4.0); vector_set(b,1,-1.0); vector_set(b,2,0.5);

    Vector* s = vector_add(a,b);
    assert(s);
    assert(s->size == 3);
    assert(s->data[0] == 5.0 && s->data[1] == 1.0 && s->data[2] == 3.5);

    int err = 0;
    double dp = vector_dot(a,b,&err);
    assert(err == 0);
    double expect = 1.0*4.0 + 2.0*(-1.0) + 3.0*0.5; // 4 -2 +1.5 = 3.5
    assert(fabs(dp - expect) < 1e-9);

    vector_free(a); vector_free(b); vector_free(s);
}

static void test_zero_and_empty() {
    Vector* a = vector_create(0);
    Vector* b = vector_create(0);
    assert(a && b);
    Vector* s = vector_add(a,b);
    assert(s && s->size == 0);
    int err = -1;
    double dp = vector_dot(a,b,&err);
    assert(err == 0 && dp == 0.0);
    vector_free(a); vector_free(b); vector_free(s);
}

static void test_mismatch_sizes() {
    Vector* a = vector_create(2);
    Vector* b = vector_create(3);
    assert(a && b);
    Vector* s = vector_add(a,b);
    assert(s == NULL);
    int err = 0;
    double dp = vector_dot(a,b,&err);
    assert(err != 0);
    vector_free(a); vector_free(b);
}

int main(void) {
    test_add_and_dot_basic();
    test_zero_and_empty();
    test_mismatch_sizes();
    printf("All tests passed.\n");
    return 0;
}
