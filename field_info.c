#include "field_info.h"

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static const char* skip_separators(const char* text) {
    while (*text != '\0' &&
           (isspace((unsigned char)*text) || *text == ',' || *text == ';')) {
        ++text;
    }
    return text;
}

static int consume_tail(const char* text) {
    text = skip_separators(text);
    if (*text == 'i' || *text == 'I') {
        ++text;
    }
    text = skip_separators(text);
    return *text == '\0';
}

static void print_int(const void* value) {
    printf("%d", *(const int*)value);
}

static int parse_int(const char* input, void* out_value) {
    char* end = NULL;
    long value;

    if (input == NULL || out_value == NULL) {
        return 0;
    }

    errno = 0;
    value = strtol(input, &end, 10);
    if (end == input || errno != 0 || value < INT_MIN || value > INT_MAX) {
        return 0;
    }
    if (!consume_tail(end)) {
        return 0;
    }

    *(int*)out_value = (int)value;
    return 1;
}

static void add_int(const void* lhs, const void* rhs, void* out_value) {
    *(int*)out_value = *(const int*)lhs + *(const int*)rhs;
}

static void multiply_int(const void* lhs, const void* rhs, void* out_value) {
    *(int*)out_value = *(const int*)lhs * *(const int*)rhs;
}

static void zero_int(void* out_value) {
    *(int*)out_value = 0;
}

static void print_double(const void* value) {
    printf("%.10g", *(const double*)value);
}

static int parse_double(const char* input, void* out_value) {
    char* end = NULL;
    double value;

    if (input == NULL || out_value == NULL) {
        return 0;
    }

    errno = 0;
    value = strtod(input, &end);
    if (end == input || errno != 0) {
        return 0;
    }
    if (!consume_tail(end)) {
        return 0;
    }

    *(double*)out_value = value;
    return 1;
}

static void add_double(const void* lhs, const void* rhs, void* out_value) {
    *(double*)out_value = *(const double*)lhs + *(const double*)rhs;
}

static void multiply_double(const void* lhs, const void* rhs, void* out_value) {
    *(double*)out_value = *(const double*)lhs * *(const double*)rhs;
}

static void zero_double(void* out_value) {
    *(double*)out_value = 0.0;
}

static void print_complex(const void* value) {
    const Complex* complex_value = (const Complex*)value;

    printf("%.10g%+.10gi", complex_value->real, complex_value->imag);
}

static int parse_complex(const char* input, void* out_value) {
    char* end = NULL;
    char* imag_start = NULL;
    double real;
    double imag;
    Complex* complex_value;

    if (input == NULL || out_value == NULL) {
        return 0;
    }

    errno = 0;
    real = strtod(input, &end);
    if (end == input || errno != 0) {
        return 0;
    }

    end = (char*)skip_separators(end);
    imag_start = end;

    errno = 0;
    imag = strtod(end, &end);
    if (end == imag_start || errno != 0) {
        return 0;
    }
    if (!consume_tail(end)) {
        return 0;
    }

    complex_value = (Complex*)out_value;
    complex_value->real = real;
    complex_value->imag = imag;
    return 1;
}

static void add_complex(const void* lhs, const void* rhs, void* out_value) {
    *(Complex*)out_value = complex_add(*(const Complex*)lhs, *(const Complex*)rhs);
}

static void multiply_complex(const void* lhs, const void* rhs, void* out_value) {
    *(Complex*)out_value = complex_multiply(*(const Complex*)lhs, *(const Complex*)rhs);
}

static void zero_complex(void* out_value) {
    *(Complex*)out_value = complex_make(0.0, 0.0);
}

const FieldInfo* get_int_field_info(void) {
    static FieldInfo storage;
    static const FieldInfo* field_info = NULL;

    if (field_info == NULL) {
        storage.type_name = "int";
        storage.input_hint = "integer";
        storage.elem_size = sizeof(int);
        storage.print = print_int;
        storage.parse = parse_int;
        storage.add = add_int;
        storage.multiply = multiply_int;
        storage.zero = zero_int;
        field_info = &storage;
    }

    return field_info;
}

const FieldInfo* get_double_field_info(void) {
    static FieldInfo storage;
    static const FieldInfo* field_info = NULL;

    if (field_info == NULL) {
        storage.type_name = "double";
        storage.input_hint = "floating-point";
        storage.elem_size = sizeof(double);
        storage.print = print_double;
        storage.parse = parse_double;
        storage.add = add_double;
        storage.multiply = multiply_double;
        storage.zero = zero_double;
        field_info = &storage;
    }

    return field_info;
}

const FieldInfo* get_complex_field_info(void) {
    static FieldInfo storage;
    static const FieldInfo* field_info = NULL;

    if (field_info == NULL) {
        storage.type_name = "complex";
        storage.input_hint = "real imag";
        storage.elem_size = sizeof(Complex);
        storage.print = print_complex;
        storage.parse = parse_complex;
        storage.add = add_complex;
        storage.multiply = multiply_complex;
        storage.zero = zero_complex;
        field_info = &storage;
    }

    return field_info;
}
