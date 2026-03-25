#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "n_vector.h"

static void print_menu(void) {
    printf("\nChoose operation:\n");
    printf("1. Create and test vectors\n");
    printf("2. Add two vectors\n");
    printf("3. Subtract two vectors\n");
    printf("4. Calculate dot product\n");
    printf("0. Exit\n");
    printf("Enter choice: ");
}

static int read_menu_choice(int *choice) {
    char buffer[64];
    char *end = NULL;
    long value;

    if (!fgets(buffer, sizeof(buffer), stdin)) {
        return 0;
    }

    value = strtol(buffer, &end, 10);
    if (end == buffer) {
        printf("Invalid input. Enter a number from 0 to 4.\n");
        return -1;
    }

    while (*end != '\0') {
        if (!isspace((unsigned char)*end)) {
            printf("Invalid input. Enter a number from 0 to 4.\n");
            return -1;
        }
        end++;
    }

    if (value < INT_MIN || value > INT_MAX) {
        printf("Input is out of range.\n");
        return -1;
    }

    *choice = (int)value;
    return 1;
}

static void print_memory_error(void) {
    printf("Memory allocation failed.\n");
}

static void run_create_demo(void) {
    int int_vals[] = {1, 2, 3, 4, 5};
    double double_vals[] = {1.5, 2.5, 3.5};
    Complex complex_vals[] = {{1.0, 2.0}, {3.0, -1.0}, {0.0, 5.0}};
    NVector *v1 = create_vector(TYPE_INT, 5, int_vals);
    NVector *v2 = create_vector(TYPE_DOUBLE, 3, double_vals);
    NVector *v3 = create_vector(TYPE_COMPLEX, 3, complex_vals);

    printf("\nTesting vector creation and printing:\n");

    if (!v1 || !v2 || !v3) {
        print_memory_error();
        free_vector(v1);
        free_vector(v2);
        free_vector(v3);
        return;
    }

    printf("Integer vector: ");
    print_vector(v1);
    printf("Double vector: ");
    print_vector(v2);
    printf("Complex vector: ");
    print_vector(v3);

    free_vector(v1);
    free_vector(v2);
    free_vector(v3);
}

static void run_add_demo(void) {
    int vals1[] = {1, 2, 3};
    int vals2[] = {4, 5, 6};
    NVector *v1 = create_vector(TYPE_INT, 3, vals1);
    NVector *v2 = create_vector(TYPE_INT, 3, vals2);
    NVector *sum;

    printf("\nAdding two vectors:\n");

    if (!v1 || !v2) {
        print_memory_error();
        free_vector(v1);
        free_vector(v2);
        return;
    }

    printf("Vector 1: ");
    print_vector(v1);
    printf("Vector 2: ");
    print_vector(v2);

    sum = add_vectors(v1, v2);
    if (sum) {
        printf("Sum: ");
        print_vector(sum);
        free_vector(sum);
    } else {
        printf("Cannot add vectors (different types or dimensions)\n");
    }

    free_vector(v1);
    free_vector(v2);
}

static void run_subtract_demo(void) {
    int vals1[] = {5, 7, 9};
    int vals2[] = {2, 3, 4};
    NVector *v1 = create_vector(TYPE_INT, 3, vals1);
    NVector *v2 = create_vector(TYPE_INT, 3, vals2);
    NVector *diff;

    printf("\nSubtracting two vectors:\n");

    if (!v1 || !v2) {
        print_memory_error();
        free_vector(v1);
        free_vector(v2);
        return;
    }

    printf("Vector 1: ");
    print_vector(v1);
    printf("Vector 2: ");
    print_vector(v2);

    diff = subtract_vectors(v1, v2);
    if (diff) {
        printf("Difference: ");
        print_vector(diff);
        free_vector(diff);
    } else {
        printf("Cannot subtract vectors (different types or dimensions)\n");
    }

    free_vector(v1);
    free_vector(v2);
}

static void run_dot_product_demo(void) {
    int vals1[] = {1, 2, 3};
    int vals2[] = {4, 5, 6};
    NVector *v1 = create_vector(TYPE_INT, 3, vals1);
    NVector *v2 = create_vector(TYPE_INT, 3, vals2);
    void *dp;

    printf("\nCalculating dot product:\n");

    if (!v1 || !v2) {
        print_memory_error();
        free_vector(v1);
        free_vector(v2);
        return;
    }

    printf("Vector 1: ");
    print_vector(v1);
    printf("Vector 2: ");
    print_vector(v2);

    dp = dot_product(v1, v2);
    if (dp) {
        printf("Dot product: ");
        print_scalar(v1->type, dp);
        printf("\n");
        free(dp);
    } else {
        printf("Cannot calculate dot product (different types or dimensions)\n");
    }

    free_vector(v1);
    free_vector(v2);
}

int main(void) {
    int choice = -1;

    printf("=== N-Dimensional Vector Calculator ===\n");

    while (choice != 0) {
        int status;

        print_menu();
        status = read_menu_choice(&choice);
        if (status == 0) {
            printf("\nInput closed. Exiting...\n");
            break;
        }
        if (status < 0) {
            continue;
        }

        switch (choice) {
            case 1:
                run_create_demo();
                break;
            case 2:
                run_add_demo();
                break;
            case 3:
                run_subtract_demo();
                break;
            case 4:
                run_dot_product_demo();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    }

    return 0;
}
