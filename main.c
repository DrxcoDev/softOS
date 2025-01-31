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
    print_msg("Kernel main has started!\n", 0x07);

    init_memory();   // Inicializamos la memoria
    print_msg("Memory initialized.\n", 0x07);

    init_idt();      // Inicializamos la IDT
    print_msg("IDT initialized.\n", 0x07);

    init_keyboard(); // Inicializamos el teclado
    print_msg("Keyboard initialized.\n", 0x07);

    print_msg("Entering main loop.\n", 0x07);
    char line[256];
    while (1) {
        print_prompt();
        read_line(line, sizeof(line));
        print_msg("\n", 0x07); // Nueva l�nea despu�s de la entrada

        // Procesar el comando ingresado
        if (line[0] != '\0') {
            char **args = parse_line(line);
            if (args != NULL) {
                int status = execute_command(args);
                if (status == 0) {
                    break; // Salir de la shell
                }
            }
        }
    }
}