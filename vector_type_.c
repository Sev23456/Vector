#include <stdio.h>
#include <stdlib.h>
#include "vector_type_.h"
#include "math.c"

#define PROCESS(ptr) process((ptr), sizeof(*(ptr)))

Vector* vector_create(FieldInfo* fieldinfo) {
    Vector* vector = (Vector*)malloc(sizeof(Vector*));

    if (vector == NULL) {
        return NULL;
    }

    vector->capacity = 4;
    vector->size = 0;
    vector->fieldinfo = fieldinfo;

    vector->data = malloc(vector->capacity * vector->fieldinfo->elem_size);

    if (vector->data = NULL) {
        free(vector);
        return NULL;
    }

    return vector;
}

void remove_data(Vector* vector) {
    free(vector->data);
    free(vector);
}

static void* vector_get_ptr(Vector* vector, size_t index) {
    return (char*)vector->data + index * vector->fieldinfo->elem_size;
}

void* add_value(Vector* vector, void* elem) {
    
    if (vector == NULL) {
        return;
    }

    if (vector->size >= vector->capacity) {
        vector->capacity *= 2;
        void* tmp_data = realloc(vector->data, vector->capacity * vector->fieldinfo->elem_size);

        if (tmp_data == NULL) {
            printf("Memory error");
            return;
        }

        vector->data = tmp_data;
    }

    memcpy(vector_get_ptr(vector, vector->size), elem, vector->fieldinfo->elem_size);

    vector->size++;
}

void* print_vector(Vector* vector) {

    if (vector->size == 0) {
        printf("Vector is initialized");
        return;
    }

    for (int elem_i = 0; elem_i < vector->size; elem_i++) {
        vector->fieldinfo->print(vector_get_ptr(vector, elem_i));
    }
}

void* vector_get(Vector* vector, size_t index) {

    if (index >= vector->size) {
        return NULL;
    }

    return (char*)vector->data + index * vector->fieldinfo->elem_size;
}

void* change_value(Vector* vector, void* elem, void* index) {
    
    if (vector == NULL) {
        return;
    }

    if (vector->size >= vector->capacity) {
        vector->capacity *= 2;
        void* tmp_data = realloc(vector->data, vector->capacity * vector->fieldinfo->elem_size);

        if (tmp_data == NULL) {
            printf("Memory error");
            return;
        }

        vector->data = tmp_data;
    }

    memcpy(vector_get_ptr(vector, index), elem, vector->fieldinfo->elem_size);

    vector->size++;
}

Vector* vector_Sum(Vector* vector_1, Vector* vector_2) {
    
    if (vector_1 != NULL && vector_2 != NULL && vector_1->fieldinfo == vector_2->fieldinfo && vector_1->capacity == vector_2->capacity) {
        
        Vector* result = vector_create(vector_1->fieldinfo);

        for (int counter = 0; counter < vector_1->capacity; counter++) {
            void* value_1 = vector_get(vector_1, counter);
            void* value_2 = vector_get(vector_2, counter);
            void* result; sum(value_1, value_2, result, PROCCESS(value_1)); // Переделать для комплексных чисел
            add_value(result, counter);
        }

        return result;
    }
}

void* scalar_product(Vector* vector_1, Vector* vector_2, void* result, DataType type) {
    if (vector_1 == NULL || vector_2 == NULL || result == NULL ||
        vector_1->size != vector_2->size ||
        vector_1->fieldinfo != vector_2->fieldinfo) {
        return NULL;
    }

    // Предполагается, что result указывает на переменную нужного типа (например, double или Complex)
    memset(result, 0, vector_1->fieldinfo->elem_size); // Инициализируем результат нулём

    for (size_t i = 0; i < vector_1->size; i++) {
        void* elem1 = vector_get(vector_1, i);
        void* elem2 = vector_get(vector_2, i);

        // Временная переменная для хранения произведения
        void* product = malloc(vector_1->fieldinfo->elem_size);
        multiply(elem1, elem2, product, type);

        // Прибавляем произведение к результату
        sum(result, product, result, type);

        free(product);
    }

    return result;
}