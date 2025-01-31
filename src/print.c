#include "../include/print.h"

char *vgaBuff = (char *)0xb8000; // VGA text buffer is located at physical address 0xb8000
int vgaBuffPos = 0;              // Position of VGA buffer

void clear_screen(void)
{
    int screen_size = VGA_WIDTH * VGA_HEIGHT * 2; // Total size of screen in bytes

    for (int i = 0; i < screen_size; i++)
    {
        vgaBuff[i] = 0;
    }
    vgaBuffPos = 0; // Reset buffer position after clearing
}

void handle_next_line(void)
{
    // Move to the start of the next line
    vgaBuffPos = (vgaBuffPos / (VGA_WIDTH * 2) + 1) * (VGA_WIDTH * 2);

    // Check if we need to scroll
    if (vgaBuffPos >= VGA_WIDTH * VGA_HEIGHT * 2)
    {
        // Scroll the screen up by one line
        for (int i = 0; i < (VGA_WIDTH * (VGA_HEIGHT - 1)) * 2; i++)
        {
            vgaBuff[i] = vgaBuff[i + VGA_WIDTH * 2];
        }

        // Clear the last line
        for (int i = (VGA_WIDTH * (VGA_HEIGHT - 1)) * 2; i < VGA_WIDTH * VGA_HEIGHT * 2; i++)
        {
            vgaBuff[i] = 0;
        }

        // Position cursor at the beginning of the last line
        vgaBuffPos = (VGA_WIDTH * (VGA_HEIGHT - 1)) * 2;
    }
}

void print_msg(char* msg, unsigned char color) {
    int i = 0;
    int pos = vgaBuffPos; // Local variable to hold buffer position

    while (msg[i] != '\0') {
        if (msg[i] == '\n') {
            handle_next_line();
            i++;
            pos = vgaBuffPos; // Update local position after handling new line
            continue;
        }

        vgaBuff[pos] = msg[i];
        vgaBuff[pos + 1] = color;

        i++;
        pos += 2;
    }

    vgaBuffPos = pos; // Update global buffer position
}