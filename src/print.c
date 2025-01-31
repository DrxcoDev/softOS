#include "../include/print.h"
#include "../include/io.h"

#include <stddef.h> 

static uint16_t* const VGA_BUFFER = (uint16_t*)0xB8000;
static const int VGA_WIDTH = 80;
static const int VGA_HEIGHT = 25;
static int vga_row = 0;
static int vga_column = 0;
static uint8_t vga_color = 0x07; // Color blanco

static uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}

void clear_screen() {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            const int index = y * VGA_WIDTH + x;
            VGA_BUFFER[index] = vga_entry(' ', vga_color);
        }
    }
    vga_row = 0;
    vga_column = 0;
}

void print_msg(const char *msg, uint8_t color) {
    for (size_t i = 0; msg[i] != '\0'; i++) {
        if (msg[i] == '\n') {
            vga_column = 0;
            if (++vga_row == VGA_HEIGHT) {
                vga_row = 0;
            }
        } else {
            const int index = vga_row * VGA_WIDTH + vga_column;
            VGA_BUFFER[index] = vga_entry(msg[i], color);
            if (++vga_column == VGA_WIDTH) {
                vga_column = 0;
                if (++vga_row == VGA_HEIGHT) {
                    vga_row = 0;
                }
            }
        }
    }
}