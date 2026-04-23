#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct Complex {
    double real;
    double imag;
} Complex;

Complex complex_make(double real, double imag);
Complex complex_add(Complex lhs, Complex rhs);
Complex complex_multiply(Complex lhs, Complex rhs);
int complex_equal(Complex lhs, Complex rhs, double eps);

#endif
