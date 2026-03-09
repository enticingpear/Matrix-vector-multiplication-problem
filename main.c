#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "multiplication.h"
#include <time.h>
#include <errno.h>

#define MIN 0
#define MAX 99

static int vectors_equal(long *a, long *b, long n) {
    for (long i = 0; i < n; ++i) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char **argv) 
{
    if (argc != 3) {
        perror("Usage: ./main <num_rows> <num_columns>");
        exit(1);
    }
    srand(time(NULL));
    
    long num_rows = strtol(argv[1], NULL, 10);
    long num_cols = strtol(argv[2], NULL, 10);

    long *matrix = (long *)calloc(num_cols * num_rows, sizeof(long));
    long *vector = (long *)calloc(num_cols, sizeof(long));

    for (long i = 0; i < num_rows; ++i) {
        for (long j = 0; j < num_cols; ++j) {
            matrix[i * num_cols + j] = rand() % (MAX - MIN + 1) + MIN;
        }
    }

    for (long i = 0; i < num_cols; ++i) {
        vector[i] = rand() % (MAX - MIN + 1) + MIN;
    }

    long *student = matrix_vector_multiplication(matrix, vector, num_rows, num_cols);
    long *reference = reference_matrix_vector_multiplication(matrix, vector, num_rows, num_cols);

    if (student == NULL) {
        printf("Implementation missing\n");
        free(matrix);
        free(vector);
        exit(1);
    }

    if (vectors_equal(student, reference, num_rows)) {
        printf("Correct\n");
    } else {
        printf("Incorrect\n");
        printf("Student result:\n");
        for (long i = 0; i < num_rows; ++i) {
            printf("%ld ", student[i]);
        }
        printf("\nReference result:\n");
        for (long i = 0; i < num_rows; ++i) {
            printf("%ld ", reference[i]);
        }
        printf("\n");
    }

    free(matrix);
    free(vector);
    free(student);
    free(reference);

    return 0;
}