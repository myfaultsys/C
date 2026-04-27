#include <stdio.h>
#include <string.h>

void decrypt_string(char* input) {
    if (!input) return;
    char buffer[4096];
    size_t len = strlen(input);
    for (size_t i = 0; i < len; i++) {
        buffer[i] = (input[i] + 1) + '0'; // Combined copy and math
    }
    buffer[len] = '\0';
    printf("Decrypted: %s\n", buffer);
}

void encrypt_string(char* input) {
    if (!input) return;
    char buffer[4096];
    size_t len = strlen(input);
    for (size_t i = 0; i < len; i++) {
        buffer[i] = (input[i] - '0') - 1;
    }
    buffer[len] = '\0';
    printf("Encrypted: %s\n", buffer);
}

int main(int argc, char** argv) {
    if (argc < 2) return 1;

    // Search for the flag anywhere in the arguments
    int decrypt_mode = 0;
    char* target_string = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0) decrypt_mode = 1;
        else target_string = argv[i]; // The argument that isn't "-d" is our string
    }

    if (decrypt_mode && target_string) decrypt_string(target_string);
    else if (target_string) encrypt_string(target_string);

    return 0;
}
