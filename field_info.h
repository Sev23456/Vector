#ifndef FIELD_INFO_H
#define FIELD_INFO_H

#include <stddef.h>

typedef struct FieldInfo {
    size_t elem_size;
    void (*print)(const void* elem);
} FieldInfo;

#endif