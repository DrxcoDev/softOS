#ifndef PRINT_H
#define PRINT_H

#include <stdint.h>

void print_msg(const char *msg, uint8_t color);
void clear_screen();

#define COLOR_WHITE 0x07 // Definir el color blanco

#endif // PRINT_H