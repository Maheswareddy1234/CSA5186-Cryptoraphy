#include <stdio.h>
#include <string.h>
#include <stdint.h>

// AES block size (128 bits = 16 bytes)
#define BLOCK_SIZE 16

// Constants for block sizes
#define Rb_128 0x87
#define Rb_64  0x1B

// Function to print a block in hex
void print_block(const char *label, uint8_t *block) {
    printf("%s: ", label);
    for (int i = 0; i < BLOCK_SIZE; i++)
        printf("%02X ", block[i]);
    printf("\n");
}

// Left shift function for a block
void left_shift(uint8_t *input, uint8_t *output) {
    uint8_t carry = 0;
    for (int i = BLOCK_SIZE - 1; i >= 0; i--) {
        uint8_t next_carry = (input[i] & 0x80) ? 1 : 0;
        output[i] = (input[i] << 1) | carry;
        carry = next_carry;
    }
}

// Subkey generation
void generate_subkeys(uint8_t *L, uint8_t *K1, uint8_t *K2, uint8_t Rb) {
    uint8_t temp[BLOCK_SIZE];
    left_shift(L, temp);

    // K1 generation
    if (L[0] & 0x80) { // Check MSB
        temp[BLOCK_SIZE - 1] ^= Rb;
    }
    memcpy(K1, temp, BLOCK_SIZE);

    // K2 generation
    left_shift(K1, temp);
    if (K1[0] & 0x80) { // Check MSB
        temp[BLOCK_SIZE - 1] ^= Rb;
    }
    memcpy(K2, temp, BLOCK_SIZE);
}

int main() {
    // Example input: encryption result of an all-zero block
    uint8_t L[BLOCK_SIZE] = {0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89,
                             0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89};
    uint8_t K1[BLOCK_SIZE], K2[BLOCK_SIZE];

    print_block("L (Encryption of zero block)", L);

    // Generate subkeys for 128-bit block size
    generate_subkeys(L, K1, K2, Rb_128);

    print_block("K1", K1);
    print_block("K2", K2);

    return 0;
}

