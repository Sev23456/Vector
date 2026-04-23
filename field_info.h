#ifndef FIELD_INFO_H
#define FIELD_INFO_H

#include <stddef.h>

#include "complex.h"

typedef void (*FieldPrintFn)(const void* value);
typedef int (*FieldParseFn)(const char* input, void* out_value);
typedef void (*FieldBinaryOpFn)(const void* lhs, const void* rhs, void* out_value);
typedef void (*FieldZeroFn)(void* out_value);

typedef struct FieldInfo {
    const char* type_name;
    const char* input_hint;
    size_t elem_size;
    FieldPrintFn print;
    FieldParseFn parse;
    FieldBinaryOpFn add;
    FieldBinaryOpFn multiply;
    FieldZeroFn zero;
} FieldInfo;

const FieldInfo* get_int_field_info(void);
const FieldInfo* get_double_field_info(void);
const FieldInfo* get_complex_field_info(void);

#endif
