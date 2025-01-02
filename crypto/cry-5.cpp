#include <stdio.h>
#include <string.h>
#include <ctype.h>

int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; 
}

void affineEncrypt(const char *plaintext, char *ciphertext, int a, int b) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = islower(plaintext[i]) ? 'a' : 'A';
            ciphertext[i] = ((a * (plaintext[i] - base) + b) % 26 + 26) % 26 + base;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

void affineDecrypt(const char *ciphertext, char *plaintext, int a, int b) {
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        printf("Decryption not possible. 'a' must be coprime with 26.\n");
        plaintext[0] = '\0'; 
        return;
    }
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = islower(ciphertext[i]) ? 'a' : 'A';
            plaintext[i] = ((a_inv * ((ciphertext[i] - base - b + 26) % 26)) % 26 + 26) % 26 + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char plaintext[100], ciphertext[100], decrypted[100];
    int a, b;

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 

    printf("Enter the values of 'a' and 'b': ");
    scanf("%d %d", &a, &b);

    if (modInverse(a, 26) == -1) {
        printf("Invalid value of 'a'. It must be coprime with 26.\n");
        return 1;
    }

    affineEncrypt(plaintext, ciphertext, a, b);
    printf("Encrypted text: %s\n", ciphertext);

    affineDecrypt(ciphertext, decrypted, a, b);
    if (decrypted[0] != '\0') {
        printf("Decrypted text: %s\n", decrypted);
    }

    return 0;
}
