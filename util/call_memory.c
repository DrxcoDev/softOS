#include "../include/memory.h"

void pug_memory() {
    char* test_memory = (char*)kmalloc(100);
    if (test_memory != NULL) {
        print_msg("Memory allocated successfully.\n", 0x07);
        kfree(test_memory);
        print_msg("Memory freed succesfully.\n", 0x07);
    } else {
        print_msg("Memory allocation failed.\n", 0x07);
    }
}