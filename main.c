#include <stdint.h>

// Definici�n del encabezado de multiboot
__attribute__((section(".multiboot")))
const uint32_t multiboot_header[] = {
    0x1BADB002,  // M�gico
    0x00,        // Flags
    -(0x1BADB002 + 0x00) // Suma de verificaci�n
};

#include "./include/print.h"
#include "./include/memory.h"
#include "./include/shell.h"
#include "./include/keyboard.h"
#include "./include/interrupts.h"



void kernel_main() {
    clear_screen();
    init_memory();   // Inicializamos la memoria
    init_idt();      // Inicializamos la IDT
    init_keyboard(); // Inicializamos el teclado
    print_msg("kernel_main() has been called!\n", 0x02);

    while (1) {
        print_prompt();
        char *line = read_line();
        if (line == NULL) {
            print_msg("Error reading line\n", 0x04);
            continue;
        }
        char **args = parse_line(line);
        if (args == NULL) {
            print_msg("Error parsing line\n", 0x04);
            continue;
        }
        int status = execute_command(args);
        if (status == 0) {
            break; // Salir de la shell
        }
    }
}