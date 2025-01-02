#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DES_BLOCK_SIZE 8

// Initial Permutation Table
static int initial_permutation[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// Final Permutation Table
static int final_permutation[] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

void permute(unsigned char* input, unsigned char* output, int* table, int size) {
    for (int i = 0; i < size; i++) {
        int bit = (input[(table[i] - 1) / 8] >> (7 - (table[i] - 1) % 8)) & 1;
        output[i / 8] |= bit << (7 - i % 8);
    }
}

void des_encrypt(unsigned char* plaintext, unsigned char* ciphertext, unsigned char* key) {
    unsigned char permuted_input[DES_BLOCK_SIZE] = {0};
    permute(plaintext, permuted_input, initial_permutation, DES_BLOCK_SIZE * 8);
    for (int i = 0; i < DES_BLOCK_SIZE; i++) ciphertext[i] = permuted_input[i];
}

void des_decrypt(unsigned char* ciphertext, unsigned char* plaintext, unsigned char* key) {
    unsigned char permuted_output[DES_BLOCK_SIZE] = {0};
    permute(ciphertext, permuted_output, final_permutation, DES_BLOCK_SIZE * 8);
    for (int i = 0; i < DES_BLOCK_SIZE; i++) plaintext[i] = permuted_output[i];
}

int main() {
    unsigned char plaintext[DES_BLOCK_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    unsigned char key[DES_BLOCK_SIZE] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};
    unsigned char ciphertext[DES_BLOCK_SIZE] = {0};
    unsigned char decrypted[DES_BLOCK_SIZE] = {0};

    des_encrypt(plaintext, ciphertext, key);
    des_decrypt(ciphertext, decrypted, key);

    printf("Plaintext: ");
    for (int i = 0; i < DES_BLOCK_SIZE; i++) printf("%02X ", plaintext[i]);
    printf("\nCiphertext: ");
    for (int i = 0; i < DES_BLOCK_SIZE; i++) printf("%02X ", ciphertext[i]);
    printf("\nDecrypted: ");
    for (int i = 0; i < DES_BLOCK_SIZE; i++) printf("%02X ", decrypted[i]);
    printf("\n");

    return 0;
}
