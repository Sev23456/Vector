#include "vector_api.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AppState {
    Vector* vector_a;
    Vector* vector_b;
} AppState;

static void read_line(char* buffer, size_t buffer_size) {
    size_t length;

    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }

    length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
    }
}

static void wait_for_enter(void) {
    char buffer[8];

    printf("\nPress Enter to continue...");
    read_line(buffer, sizeof(buffer));
}

static int parse_menu_number(const char* text, int* out_value) {
    char* end = NULL;
    long value;

    value = strtol(text, &end, 10);
    if (end == text) {
        return 0;
    }
    while (*end == ' ' || *end == '\t') {
        ++end;
    }
    if (*end != '\0') {
        return 0;
    }

    *out_value = (int)value;
    return 1;
}

static int parse_size_value(const char* text, size_t* out_value) {
    char* end = NULL;
    unsigned long long value;

    if (text == NULL || *text == '-') {
        return 0;
    }

    value = strtoull(text, &end, 10);
    if (end == text) {
        return 0;
    }
    while (*end == ' ' || *end == '\t') {
        ++end;
    }
    if (*end != '\0') {
        return 0;
    }

    *out_value = (size_t)value;
    return 1;
}

static const FieldInfo* choose_field_info(void) {
    char line[64];
    int option;

    printf("Choose element type:\n");
    printf("1. int\n");
    printf("2. double\n");
    printf("3. complex\n");
    printf("Type: ");
    read_line(line, sizeof(line));

    if (!parse_menu_number(line, &option)) {
        return NULL;
    }

    switch (option) {
        case 1:
            return get_int_field_info();
        case 2:
            return get_double_field_info();
        case 3:
            return get_complex_field_info();
        default:
            return NULL;
    }
}

static void replace_vector(Vector** slot, Vector* new_vector) {
    vector_free(*slot);
    *slot = new_vector;
}

static int input_vector(Vector** slot, const char* name) {
    const FieldInfo* field_info;
    Vector* vector;
    void* value_buffer;
    char line[256];
    size_t count;
    size_t index;
    VectorStatus status;

    field_info = choose_field_info();
    if (field_info == NULL) {
        printf("Invalid type selection.\n");
        return 0;
    }

    printf("Enter number of elements for %s: ", name);
    read_line(line, sizeof(line));
    if (!parse_size_value(line, &count)) {
        printf("Invalid size.\n");
        return 0;
    }

    vector = vector_create(field_info, count);
    if (vector == NULL) {
        printf("Cannot create vector.\n");
        return 0;
    }

    value_buffer = malloc(field_info->elem_size);
    if (value_buffer == NULL) {
        vector_free(vector);
        printf("Allocation failed.\n");
        return 0;
    }

    for (index = 0; index < count; ++index) {
        printf(
            "Element %zu for %s (%s): ",
            index,
            name,
            field_info->input_hint
        );
        read_line(line, sizeof(line));

        if (field_info->parse == NULL || !field_info->parse(line, value_buffer)) {
            printf("Bad value format.\n");
            free(value_buffer);
            vector_free(vector);
            return 0;
        }

        status = vector_set(vector, index, value_buffer);
        if (status != VECTOR_OK) {
            printf("Cannot write element: %s.\n", vector_status_message(status));
            free(value_buffer);
            vector_free(vector);
            return 0;
        }
    }

    free(value_buffer);
    replace_vector(slot, vector);
    return 1;
}

static void print_named_vector(const char* name, const Vector* vector) {
    printf("%s = ", name);
    if (vector == NULL) {
        printf("(not created)\n");
        return;
    }

    printf("%s ", vector_field_info(vector)->type_name);
    vector_print(vector);
    printf("\n");
}

static void print_scalar_result(const Vector* vector, const void* value) {
    const FieldInfo* field_info = vector_field_info(vector);

    if (field_info == NULL) {
        printf("(unknown)\n");
        return;
    }

    field_info->print(value);
    printf("\n");
}

static void handle_sum(const AppState* state) {
    Vector* result = NULL;
    VectorStatus status = vector_sum(state->vector_a, state->vector_b, &result);

    if (status != VECTOR_OK) {
        printf("A + B failed: %s.\n", vector_status_message(status));
        return;
    }

    printf("A + B = ");
    vector_print(result);
    printf("\n");
    vector_free(result);
}

static void handle_dot(const AppState* state) {
    const FieldInfo* field_info;
    void* result;
    VectorStatus status;

    if (state->vector_a == NULL || state->vector_b == NULL) {
        printf("Create both vectors first.\n");
        return;
    }

    field_info = vector_field_info(state->vector_a);
    result = malloc(field_info->elem_size);
    if (result == NULL) {
        printf("Allocation failed.\n");
        return;
    }

    status = vector_dot(state->vector_a, state->vector_b, result);
    if (status != VECTOR_OK) {
        printf("A . B failed: %s.\n", vector_status_message(status));
        free(result);
        return;
    }

    printf("A . B = ");
    print_scalar_result(state->vector_a, result);
    free(result);
}

int main(void) {
    AppState state;
    char line[64];
    int command;

    state.vector_a = NULL;
    state.vector_b = NULL;

    while (1) {
        printf("\nPolymorphic Vector Lab\n");
        printf("1. Create or replace vector A\n");
        printf("2. Create or replace vector B\n");
        printf("3. Print vectors\n");
        printf("4. Sum vectors\n");
        printf("5. Scalar product\n");
        printf("0. Exit\n");
        printf("Choose: ");
        read_line(line, sizeof(line));

        if (!parse_menu_number(line, &command)) {
            printf("Unknown command.\n");
            wait_for_enter();
            continue;
        }

        if (command == 0) {
            break;
        }

        if (command == 1) {
            if (input_vector(&state.vector_a, "A")) {
                printf("Vector A updated.\n");
            }
            wait_for_enter();
            continue;
        }

        if (command == 2) {
            if (input_vector(&state.vector_b, "B")) {
                printf("Vector B updated.\n");
            }
            wait_for_enter();
            continue;
        }

        if (command == 3) {
            print_named_vector("A", state.vector_a);
            print_named_vector("B", state.vector_b);
            wait_for_enter();
            continue;
        }

        if (command == 4) {
            handle_sum(&state);
            wait_for_enter();
            continue;
        }

        if (command == 5) {
            handle_dot(&state);
            wait_for_enter();
            continue;
        }

        printf("Unknown command.\n");
        wait_for_enter();
    }

    vector_free(state.vector_a);
    vector_free(state.vector_b);
    return 0;
}
