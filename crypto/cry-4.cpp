#include <stdio.h>
#include <string.h>
#include <ctype.h>
void vigenere_encrypt(char *plaintext, char *key, char *ciphertext) {
    int i, j = 0;
    int len_plaintext = strlen(plaintext);
    int len_key = strlen(key);

    for (i = 0; i < len_plaintext; i++) {
        if (isalpha(plaintext[i])) {
            char shift = toupper(key[j % len_key]) - 'A';  
            if (isupper(plaintext[i])) {
                ciphertext[i] = (plaintext[i] - 'A' + shift) % 26 + 'A';
            } else {
                ciphertext[i] = (plaintext[i] - 'a' + shift) % 26 + 'a';
            }
            j++;  
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
    ciphertext[i] = '\0'; 
}

int main() {
    char plaintext[100], key[100], ciphertext[100];

    // Input the plaintext
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  // Remove the newline character

    // Input the key
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';  // Remove the newline character

    // Encrypt the plaintext using the Vigenère cipher
    vigenere_encrypt(plaintext, key, ciphertext);

    // Output the encrypted ciphertext
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

