#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Dot product function: result = sum(x[i] * y[i])
float dot(int n, float *x, float *y) {
    float result = 0.0f;
    for (int i = 0; i < n; i++) {
        result += x[i] * y[i];
    }
    return result;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <N>\n", argv[0]);
        return 1;
    }

    size_t n = (size_t)atoi(argv[1]);  // Size of the vectors from command line input

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

    // Perform the dot product
    float result = dot(n, x, y);

    // Stop the timer
    clock_t end = clock();

    // Calculate the elapsed time in seconds
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

    // Print the result and elapsed time
    printf("Dot product result: %f\n", result);
    printf("Time taken for dot product execution: %f seconds\n", elapsed_time);

    // Free the allocated memory
    free(x);
    x = NULL;
    free(y);
    y = NULL;

    return 0;
}
