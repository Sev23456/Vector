#ifndef COMPLEX_OPS_H
#define COMPLEX_OPS_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    double real;
    double imag;
} Complex;

// Объявления функций для работы с комплексными числами
Complex Sum(Complex x, Complex y);
Complex Product(Complex x, Complex y);
Complex Subtraction(Complex x, Complex y);
Complex Division(Complex x, Complex y);

#endif