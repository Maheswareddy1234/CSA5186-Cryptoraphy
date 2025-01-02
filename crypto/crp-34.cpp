#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BLOCK_SIZE 8

void xor_blocks(uint8_t* a, uint8_t* b, uint8_t* out, size_t len) {
    for (size_t i = 0; i < len; i++) {
        out[i] = a[i] ^ b[i];
    }
}

void des_encrypt_block(uint8_t* plaintext, uint8_t* ciphertext, uint8_t* key) {
    for (int i = 0; i < BLOCK_SIZE; i++) ciphertext[i] = plaintext[i] ^ key[i];
}

void des_decrypt_block(uint8_t* ciphertext, uint8_t* plaintext, uint8_t* key) {
    for (int i = 0; i < BLOCK_SIZE; i++) plaintext[i] = ciphertext[i] ^ key[i];
}

void ecb_mode(uint8_t* plaintext, uint8_t* ciphertext, uint8_t* key, size_t length) {
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        des_encrypt_block(plaintext + i, ciphertext + i, key);
    }
}

void cbc_mode(uint8_t* plaintext, uint8_t* ciphertext, uint8_t* key, uint8_t* iv, size_t length) {
    uint8_t buffer[BLOCK_SIZE];
    memcpy(buffer, iv, BLOCK_SIZE);
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        xor_blocks(plaintext + i, buffer, buffer, BLOCK_SIZE);
        des_encrypt_block(buffer, ciphertext + i, key);
        memcpy(buffer, ciphertext + i, BLOCK_SIZE);
    }
}

void cfb_mode(uint8_t* plaintext, uint8_t* ciphertext, uint8_t* key, uint8_t* iv, size_t length) {
    uint8_t buffer[BLOCK_SIZE];
    memcpy(buffer, iv, BLOCK_SIZE);
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        des_encrypt_block(buffer, buffer, key);
        xor_blocks(plaintext + i, buffer, ciphertext + i, BLOCK_SIZE);
        memcpy(buffer, ciphertext + i, BLOCK_SIZE);
    }
}

void pad_data(uint8_t* data, size_t* length) {
    size_t pad_len = BLOCK_SIZE - (*length % BLOCK_SIZE);
    data[*length] = 0x80;
    for (size_t i = 1; i < pad_len; i++) {
        data[*length + i] = 0x00;
    }
    *length += pad_len;
}

int main() {
    uint8_t plaintext[32] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    uint8_t key[BLOCK_SIZE] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};
    uint8_t iv[BLOCK_SIZE] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};
    uint8_t ciphertext[32] = {0};
    uint8_t decrypted[32] = {0};

    size_t length = 8;
    pad_data(plaintext, &length);

    printf("ECB Mode:\n");
    ecb_mode(plaintext, ciphertext, key, length);
    for (size_t i = 0; i < length; i++) printf("%02X ", ciphertext[i]);
    printf("\n");

    printf("CBC Mode:\n");
    cbc_mode(plaintext, ciphertext, key, iv, length);
    for (size_t i = 0; i < length; i++) printf("%02X ", ciphertext[i]);
    printf("\n");

    printf("CFB Mode:\n");
    cfb_mode(plaintext, ciphertext, key, iv, length);
    for (size_t i = 0; i < length; i++) printf("%02X ", ciphertext[i]);
    printf("\n");

    return 0;
}
