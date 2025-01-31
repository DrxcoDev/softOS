#include "../include/memory.h"

#define HEAP_START 0x100000
#define HEAP_SIZE  0x100000 // 1 MB heap size

typedef struct block {
    size_t size;
    struct block* next;
    int free;
} block_t;

static block_t* free_list = (block_t*)HEAP_START;

void init_memory() {
    free_list->size = HEAP_SIZE - sizeof(block_t);
    free_list->next = NULL;
    free_list->free = 1;
}

void* kmalloc(size_t size) {
    block_t* current = free_list;
    while (current != NULL) {
        if (current->free && current->size >= size) {
            if (current->size > size + sizeof(block_t)) {
                block_t* new_block = (block_t*)((char*)current + sizeof(block_t) + size);
                new_block->size = current->size - size - sizeof(block_t);
                new_block->next = current->next;
                new_block->free = 1;
                current->size = size;
                current->next = new_block;
            }
            current->free = 0;
            return (void*)((char*)current + sizeof(block_t));
        }
        current = current->next;
    }
    return NULL; // No suitable block found
}

void kfree(void* ptr) {
    if (ptr == NULL) return;

    block_t* block = (block_t*)((char*)ptr - sizeof(block_t));
    block->free = 1;

    // Coalesce adjacent free blocks
    block_t* current = free_list;
    while (current != NULL) {
        if (current->free && current->next && current->next->free) {
            current->size += current->next->size + sizeof(block_t);
            current->next = current->next->next;
        }
        current = current->next;
    }
}