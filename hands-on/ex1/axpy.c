#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void axpy(int n, float a, float *x, float *y) {
    for (int i = 0; i < n; i++) {
        y[i] = a * x[i] + y[i];
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <N>\n", argv[0]);
        return 1;
    }

    size_t n = (size_t)atoi(argv[1]);  // Size of the vectors from command line input
    float a = 2.0f;                    // Scalar multiplier

    // Allocate memory for the vectors
    float *x = (float*) malloc(n * sizeof(float));
    float *y = (float*) malloc(n * sizeof(float));

    // Check for successful memory allocation
    if (x == NULL || y == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the vectors
    for (int i = 0; i < n; i++) {
        x[i] = 1.0f;
        y[i] = 2.0f;
    }

    // Start the timer
    clock_t start = clock();

    // Perform the AXPY operation
    axpy(n, a, x, y);

    // Stop the timer
    clock_t end = clock();

    // Calculate the elapsed time in seconds
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

    // Print the elapsed time
    printf("Time taken for axpy execution: %f seconds\n", elapsed_time);

    // Free the allocated memory
    free(x);
    x = NULL;
    free(y);
    y = NULL;

    return 0;
}
