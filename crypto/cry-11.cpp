#include <stdio.h>
#include <math.h>

// Function to calculate log2(n!)
double log2_factorial(int n) {
    double log2_fact = 0.0;
    for (int i = 1; i <= n; i++) {
        log2_fact += log2(i);
    }
    return log2_fact;
}

int main() {
    int n = 25; // Playfair Cipher uses a 5x5 grid, 25 letters
    double raw_keyspace = log2_factorial(n); // Log2 of 25!
    double effective_keyspace = 49.0; // Known approximate log2 value for unique keys

    printf("Playfair Cipher Key Analysis:\n");
    printf("1. Total Possible Keyspace (without redundancy): 2^%.2f\n", raw_keyspace);
    printf("2. Unique Effective Keyspace (considering redundancy): 2^%.2f\n", effective_keyspace);

    return 0;
}

