#ifndef COMPLEX_H
#define COMPLEX_H

#include <stdlib.h>

typedef struct Complex {
    double real;
    double imag;
} Complex;

Complex add(Complex x, Complex y);

Complex product(Complex x, Complex y);

Complex subtraction(Complex x, Complex y);

Complex division(Complex x, Complex y);

#endif