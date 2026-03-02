#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector_api.h"

static void prompt_enter() {
    printf("Press Enter to continue...");
    getchar();
}

static void read_line(char* buf, size_t n) {
    if (fgets(buf, (int)n, stdin) == NULL) return;
    size_t len = strlen(buf);
    if (len && buf[len-1] == '\n') buf[len-1] = '\0';
}

int main(void) {
    Vector* a = NULL;
    Vector* b = NULL;
    char line[256];

    while (1) {
        system("cls");
        printf("Simple Vector CLI\n");
        printf("1) Create vector A\n");
        printf("2) Create vector B\n");
        printf("3) Input elements for A\n");
        printf("4) Input elements for B\n");
        printf("5) Print A and B\n");
        printf("6) A + B (prints result)\n");
        printf("7) A . B (scalar product)\n");
        printf("0) Exit\n");
        printf("Choose: ");
        read_line(line, sizeof(line));

        int cmd = atoi(line);
        if (cmd == 0) break;

        if (cmd == 1 || cmd == 2) {
            printf("Enter dimension (non-negative integer): ");
            read_line(line, sizeof(line));
            long n = atol(line);
            if (n < 0) {
                printf("Invalid size\n"); prompt_enter(); continue;
            }
            Vector* v = vector_create((size_t)n);
            if (!v) { printf("Allocation failed\n"); prompt_enter(); continue; }
            if (cmd == 1) { if (a) vector_free(a); a = v; } else { if (b) vector_free(b); b = v; }
            printf("Vector created (size=%zu)\n", v->size);
            prompt_enter();
            continue;
        }

        if (cmd == 3 || cmd == 4) {
            Vector* v = (cmd == 3) ? a : b;
            if (!v) { printf("Vector not created yet\n"); prompt_enter(); continue; }
            for (size_t i = 0; i < v->size; i++) {
                printf("Enter element [%zu]: ", i);
                read_line(line, sizeof(line));
                double val = atof(line);
                vector_set(v, i, val);
            }
            printf("Values set\n"); prompt_enter(); continue;
        }

        if (cmd == 5) {
            printf("Vector A:\n"); if (a) vector_print(a); else printf("(not created)\n");
            printf("Vector B:\n"); if (b) vector_print(b); else printf("(not created)\n");
            prompt_enter(); continue;
        }

        if (cmd == 6) {
            if (!a || !b) { printf("Both vectors must be created\n"); prompt_enter(); continue; }
            Vector* sum = vector_add(a, b);
            if (!sum) { printf("Addition failed (size mismatch?)\n"); prompt_enter(); continue; }
            printf("A + B =\n"); vector_print(sum); vector_free(sum); prompt_enter(); continue;
        }

        if (cmd == 7) {
            if (!a || !b) { printf("Both vectors must be created\n"); prompt_enter(); continue; }
            int err = 0;
            double dp = vector_dot(a, b, &err);
            if (err) { printf("Dot product failed (size mismatch?)\n"); prompt_enter(); continue; }
            printf("A . B = %.10g\n", dp); prompt_enter(); continue;
        }

        printf("Unknown option\n"); prompt_enter();
    }

    if (a) vector_free(a);
    if (b) vector_free(b);
    return 0;
}