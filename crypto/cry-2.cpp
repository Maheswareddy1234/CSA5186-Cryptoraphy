#include <stdio.h>
#include <string.h>

void monoalphabetic_cipher(char *text, char *key) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = key[text[i] - 'A'];
        } else if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = key[text[i] - 'a'] + 32;  
        }
    }
}

int main() {
    char text[100];
    char key[26];

    printf("Enter the plaintext: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter the substitution key (26 characters): ");
    fgets(key, sizeof(key), stdin);
    text[strcspn(text, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';
    monoalphabetic_cipher(text, key);
    printf("Encrypted text: %s\n", text);

    return 0;
}

