#include <stdio.h>
#include <string.h>
#include <openssl/des.h>
#include <openssl/rand.h>

#define BLOCK_SIZE 8

// Function to print data in hexadecimal format
void printHex(const char *label, const unsigned char *data, int length) {
    printf("%s: ", label);
    for (int i = 0; i < length; i++) {
        printf("%02X", data[i]);
    }
    printf("\n");
}

// 3DES CBC Encryption
void encrypt3DES_CBC(const unsigned char *plaintext, int plaintext_len,
                     unsigned char *ciphertext, unsigned char *key, unsigned char *iv) {
    DES_cblock key1, key2, key3;
    DES_key_schedule ks1, ks2, ks3;

    // Split the key into three DES keys
    memcpy(key1, key, 8);
    memcpy(key2, key + 8, 8);
    memcpy(key3, key + 16, 8);

    // Set up key schedules
    DES_set_key_unchecked(&key1, &ks1);
    DES_set_key_unchecked(&key2, &ks2);
    DES_set_key_unchecked(&key3, &ks3);

    // Padding to make plaintext a multiple of BLOCK_SIZE
    unsigned char padded_plaintext[BLOCK_SIZE * ((plaintext_len / BLOCK_SIZE) + 1)];
    int padding = BLOCK_SIZE - (plaintext_len % BLOCK_SIZE);
    memcpy(padded_plaintext, plaintext, plaintext_len);
    for (int i = 0; i < padding; i++) {
        padded_plaintext[plaintext_len + i] = padding;
    }

    int padded_len = plaintext_len + padding;

    // Perform CBC encryption
    DES_cblock iv_block;
    memcpy(iv_block, iv, BLOCK_SIZE);

    for (int i = 0; i < padded_len; i += BLOCK_SIZE) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            padded_plaintext[i + j] ^= iv_block[j];
        }

        DES_ecb3_encrypt((DES_cblock *)(padded_plaintext + i),
                         (DES_cblock *)(ciphertext + i),
                         &ks1, &ks2, &ks3, DES_ENCRYPT);

        memcpy(iv_block, ciphertext + i, BLOCK_SIZE);
    }
}

int main() {
    unsigned char plaintext[] = "Hello, this is a 3DES CBC encryption example!";
    unsigned char key[24]; // 3DES requires a 24-byte key
    unsigned char iv[BLOCK_SIZE]; // 8-byte initialization vector
    unsigned char ciphertext[1024];

    // Generate a random key and IV
    if (!RAND_bytes(key, sizeof(key)) || !RAND_bytes(iv, sizeof(iv))) {
        printf("Error generating random key or IV.\n");
        return 1;
    }

    printf("3DES CBC Encryption Example\n");
    printHex("Key", key, sizeof(key));
    printHex("IV", iv, sizeof(iv));

    // Perform encryption
    int plaintext_len = strlen((char *)plaintext);
    encrypt3DES_CBC(plaintext, plaintext_len, ciphertext, key, iv);

    printHex("Plaintext", plaintext, plaintext_len);
    printHex("Ciphertext", ciphertext, ((plaintext_len / BLOCK_SIZE) + 1) * BLOCK_SIZE);

    return 0;
}

