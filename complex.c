#include <stdlib.h>
#include "complex.h"

Complex add(Complex x, Complex y) { // Сумма
    return (Complex){x.real + y.real, x.imag + y.imag};
}

Complex product(Complex x, Complex y) { // Произведение
    return (Complex){x.real * y.real - x.imag * y.imag, x.real * y.imag + x.imag * y.real};
}

Complex subtraction(Complex x, Complex y) { // Вычитание
    return (Complex){x.real - y.real, x.imag - y.imag};
}

Complex division(Complex x, Complex y) {
    double denom = y.real*y.real+y.imag*y.imag; // Деление
    if (denom==0) {
        printf("Error: Division by zero complex number\n");
        exit(EXIT_FAILURE);
    }
    return (Complex){(x.real*y.real+x.imag*y.imag)/denom};
}