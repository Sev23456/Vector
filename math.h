#include "complex.c"

// Перечисление типов для runtime-проверки
typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_COMPLEX
} DataType;

void* sum(void* a, void* b, void* result, DataType type);

void* multiply(void* a, void* b, void* result, DataType type);
