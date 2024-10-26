#include "./include/print.h"

void delay(int time)
{
    for (int i = 0; i < time * 1000000; i++)
    {
        __asm__("nop");  // No Operation, hace que la CPU no haga nada en cada iteración
    }
}

void kernel_main() {
    // Simple usage of print_msg() to print a string to the screen
    clear_screen();
    print_msg("kernel_main() has been called!\n", 0x02);
    delay(100); 
    print_msg("Succes!\n", 0x02);
}
