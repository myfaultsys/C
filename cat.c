#include <stdio.h>

void print_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file==NULL) {
        printf("\nUnable to open file %s\n", filename);
        return;
    }
    //reading characters in unsigned integer format <-> argument object for putchar
    int ch;
    //fgetc reads byte from file and moeves to next one after reading ie runs loop
    while ((ch = fgetc(file)) != EOF) {
    //putchar takes character and translates to ascii and increments to next char
        putchar(ch);
    }
    fclose(file);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("\nUsage: ./cat <file1> <file2> ...");
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        //printf("%s:\n", argv[i]);
        print_file(argv[i]);
        printf("\n");
    }
    return 0;
}
