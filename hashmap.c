#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 7
#define DELETED_NODE (person *)(0xFFFFFFFFFFFFFFFFUL)

typedef struct {
    char name[MAX_NAME];
    int age;
    // .... add other info later
} person;

person *hash_table[TABLE_SIZE];

unsigned int hash(char *name) {
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0;
    for (int i = 0; i < length; i++) {
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
    }
    return hash_value;
}

void init_hash_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}

void print_table() {
    printf("\tStart ###########\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] == NULL) {
            printf("\t%i\t---------\n", i);
        } else if (hash_table[i] == DELETED_NODE) {
            printf("\t%i\t<deleted>\n",i);
        } else {
            printf("\t%i\t%s\n",i,  hash_table[i]->name);
        }
     }
    printf("\tEnd #############\n");
}

bool hash_table_insert(person *p) {
    if (p == NULL) return false;
    int index = hash(p->name);

    for (int i = 0; i < TABLE_SIZE; i++) {
        int try = (i + index) % TABLE_SIZE;
        if (hash_table[try] == NULL || hash_table[try] == DELETED_NODE) {
            hash_table[try] = p;
            return true;
        }
    }
    return true;
}

person *hash_table_lookup(char *name) {
    int index = hash(name); 
    for (int i = 0; i < TABLE_SIZE; i++) {
        int try = (i + index) % TABLE_SIZE;
        if (hash_table[try] == NULL) {
            return false;
        }
        if (hash_table[try] == DELETED_NODE) continue;
        if (hash_table[try] != NULL && strncpy(hash_table[try]->name, name, MAX_NAME) == 0) {
        return hash_table[try];
        }
    }
    return NULL;
}

person *hash_table_delete(char *name) {
    int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int try = (i + index) % TABLE_SIZE;
        if (hash_table[try] == NULL) return NULL;
        if (hash_table[try] == DELETED_NODE) continue;
        if (hash_table[try] != NULL && strncmp(hash_table[try]->name, name, TABLE_SIZE) == 0) {
            person *tmp = hash_table[try];
            hash_table[try] = (person *)(0xFFFFFFFFFFFFFFFFUL);
            return tmp;
        }
    }
    return NULL;
}

int main(int argc, char **argv) {

    init_hash_table();
    print_table();

    person cow = {.name = "cow", .age=2};
    person cat = {.name = "cat", .age=5};

    hash_table_insert(&cow);
    hash_table_insert(&cat);

    print_table();

    hash_table_delete("cat");

    print_table();

    return 0;
}
