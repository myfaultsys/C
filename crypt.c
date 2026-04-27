#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { ENCRYPT, DECRYPT } mode;

void decrypt_string(char* string) {
	char buffer[4096];
	size_t length = strlen(string);
	for (unsigned i = 0; i < length; i++) {
		*(buffer + i) = *(string + i);
	}
	for (unsigned i = 0; i < length;  i++) {
		*(buffer + i) = ( ( *(buffer + i)) + 1 ) + '0';
	}
	buffer[length] = '\0';
	printf("The decrypted string is: %s\n", buffer);
};

void discombobulate(char* buffer, size_t length) {
	for (unsigned i = 0; i < length; i++) {
		*(buffer + i) = ( ( *(buffer + i)) - '0' ) - 1;
	}
}

void encrypt_string(char* string) {	
	char buffer[4096];
	size_t length = strlen(string);
	for (unsigned i = 0; i < length; i++) {
		buffer[i] = *(string++);
	}
	buffer[length] = '\0';
	discombobulate(buffer, length);
	printf("Encrypted string is: %s\n", buffer);
};

int main(int argc, char** argv) {
	
	mode program_mode = ENCRYPT;
	
	int arg_indexes[argc];
	memset(arg_indexes, 0, argc);

	for (unsigned i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-d")) {
			arg_indexes[i] = 1;
			program_mode = DECRYPT;
		}
	}

	switch (program_mode) {
		case ENCRYPT:
			encrypt_string(argv[1]);
			break;
		case DECRYPT:
			decrypt_string(argv[2]);
	}

	return 0;
}
