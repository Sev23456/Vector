#ifndef COMPLEX_H
#define COMPLEX_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    double real;
    double imag;
} Complex;

Complex Sum(Complex x, Complex y);
Complex Product(Complex x, Complex y);
Complex Subtraction(Complex x, Complex y);
Complex Division(Complex x, Complex y);

#endif // COMPLEX_H