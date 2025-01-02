#include <stdio.h>
#include <ctype.h>
#include <string.h>

void caesarCipher(char *text, int key) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = islower(text[i]) ? 'a' : 'A';
            text[i] = (text[i] - base + key) % 26 + base;
        }
    }
}

int main() {
    char text[100];
    int key;

    printf("Enter the text to encrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; 
    
    printf("Enter the key (1-25): ");
    scanf("%d", &key);

    if (key < 1 || key > 25) {
        printf("Invalid key. Please enter a value between 1 and 25.\n");
        return 1;
    }

    caesarCipher(text, key);

    printf("Encrypted text: %s\n", text);

    return 0;
}
