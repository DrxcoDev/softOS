#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

void init_memory();
void* kmalloc(size_t size);
void kfree(void* ptr);

#endif // MEMORY_H