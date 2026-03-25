#include "complex_ops.h"

Complex Sum(Complex x, Complex y) { // Сумма
    return (Complex){x.real + y.real, x.imag + y.imag};
}

Complex Product(Complex x, Complex y) { // Произведение
    return (Complex){x.real * y.real - x.imag * y.imag, x.real * y.imag + x.imag * y.real};
}

Complex Subtraction(Complex x, Complex y) { // Вычитание
    return (Complex){x.real - y.real, x.imag - y.imag};
}

Complex Division(Complex x, Complex y) {
    double denom = y.real*y.real+y.imag*y.imag; // Деление
    if (denom==0) {
        printf("Error: Division by zero complex number\n");
        exit(EXIT_FAILURE);
    }
    return (Complex){(x.real*y.real+x.imag*y.imag)/denom, (x.imag*y.real-x.real*y.imag)/denom};
}