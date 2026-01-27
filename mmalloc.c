#include "mmalloc.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define BLOCKSIZE 8
#define ALIGN(x) ( (x + BLOCKSIZE - 1) & ~(BLOCKSIZE - 1) )
#define MMAP_THRHLD ( 128 * 1024 );

// check for errors and exit if critical fail
#define FAIL(assertion, call_descr) \
    do {                            \
        if (assertion) {            \
            perror(call_descr);     \
            exit(EXIT_FAILURE);     \
        }                           \
    } while (0)                     \

typedef enum {
    STATUS_FREE,
    STATUS_ALLOC,
    STATUS_MAPPED
} block_status;

typedef struct blockmeta {
    size_t size;
    block_status status;
    struct blockmeta *next;
    struct blockmeta *prev;
} blockmeta_t;

static blockmeta_t *head = NULL;
static bool preallocated = false;

static blockmeta_t *request_space(size_t  size, blockmeta_t *last_entry) {
    blockmeta_t *block = sbrk(sizeof(blockmeta_t) + size);
    if (block == (void *)-1) {
        perror("sbrk fail");
        return NULL;
    }
    block->size = size;
    block->status = STATUS_ALLOC;
    block->next = NULL;
    block->prev = last_entry;
    if (last_entry) {
        last_entry->next = block;
    } else {
        head = block;
    }
    return block;
}

static blockmeta_t *find_last_entry(void) {
    blockmeta_t *curr = head;
    if (!curr) return NULL;
    while (curr->next) {
        curr = curr->next;
    }
    return curr;
}

void *mmalloc(size_t size) {
    if (size == 0) return NULL;
    size = ALIGN(size);
    blockmeta_t *last_entry = find_last_entry();
    blockmeta_t *new_block = request_space(size, last_entry);
    if (!new_block) return NULL;
    return (void *)(new_block + 1);
}

void *mcalloc(size_t arrcount, size_t size) {
    // implementation
    (void)arrcount; (void)size;
    fprintf(stderr, "mcalloc has no implementation\n");
    return NULL;
}

void *mrealloc(void *ptr, size_t size) {
    // implementation
    (void)ptr; (void)size;
    fprintf(stderr, "mrealloc has no implementation\n");
    return NULL;
}

void mfree(void *ptr) {
    // implementation
    (void)ptr;
    fprintf(stderr, "mfree has no implementation\n");
}


typedef struct node {
    int val;
    struct node *next;
} node_t;


