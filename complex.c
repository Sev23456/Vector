#include "complex.h"

#include <math.h>

Complex complex_make(double real, double imag) {
    Complex value;

    value.real = real;
    value.imag = imag;
    return value;
}

Complex complex_add(Complex lhs, Complex rhs) {
    return complex_make(lhs.real + rhs.real, lhs.imag + rhs.imag);
}

Complex complex_multiply(Complex lhs, Complex rhs) {
    return complex_make(
        lhs.real * rhs.real - lhs.imag * rhs.imag,
        lhs.real * rhs.imag + lhs.imag * rhs.real
    );
}

int complex_equal(Complex lhs, Complex rhs, double eps) {
    return fabs(lhs.real - rhs.real) <= eps && fabs(lhs.imag - rhs.imag) <= eps;
}
