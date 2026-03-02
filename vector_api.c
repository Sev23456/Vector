#include "vector_api.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Vector* vector_create(size_t n) {
    Vector* v = (Vector*)malloc(sizeof(Vector));
    if (!v) return NULL;
    v->size = n;
    if (n == 0) {
        v->data = NULL;
    } else {
        v->data = (double*)calloc(n, sizeof(double));
        if (!v->data) { free(v); return NULL; }
    }
    return v;
}

void vector_free(Vector* v) {
    if (!v) return;
    free(v->data);
    free(v);
}

int vector_set(Vector* v, size_t idx, double val) {
    if (!v || idx >= v->size) return 0;
    v->data[idx] = val;
    return 1;
}

double vector_get(const Vector* v, size_t idx) {
    if (!v || idx >= v->size) return 0.0;
    return v->data[idx];
}

Vector* vector_add(const Vector* a, const Vector* b) {
    if (!a || !b) return NULL;
    if (a->size != b->size) return NULL;
    Vector* r = vector_create(a->size);
    if (!r) return NULL;
    for (size_t i = 0; i < a->size; i++) r->data[i] = a->data[i] + b->data[i];
    return r;
}

double vector_dot(const Vector* a, const Vector* b, int* err) {
    if (err) *err = 1;
    if (!a || !b) return 0.0;
    if (a->size != b->size) return 0.0;
    double sum = 0.0;
    for (size_t i = 0; i < a->size; i++) sum += a->data[i] * b->data[i];
    if (err) *err = 0;
    return sum;
}

void vector_print(const Vector* v) {
    if (!v) { printf("(null)\n"); return; }
    printf("size=%zu [", v->size);
    for (size_t i = 0; i < v->size; i++) {
        if (i) printf(", ");
        printf("%.10g", v->data[i]);
    }
    printf("]\n");
}
