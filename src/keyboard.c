#include "../include/io.h"  // Asegúrate de incluir el archivo de cabecera
#include "../include/keyboard.h"
#include "../include/print.h"
#include "../include/interrupts.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_IRQ 1
#define BUFFER_SIZE 256

static char keymap[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z',
    'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3',
    '0', '.'
};

static char buffer[BUFFER_SIZE];
static int buffer_index = 0;

void keyboard_handler() {
    unsigned char status;
    char keycode;

    // Leer el estado del puerto del teclado
    status = inb(KEYBOARD_STATUS_PORT);

    // Si el bit 0 del estado es 1, hay datos disponibles en el puerto de datos
    if (status & 0x01) {
        keycode = inb(KEYBOARD_DATA_PORT);

        // Si el keycode es negativo, es una liberaci�n de tecla
        if (keycode < 0) {
            return;
        }

        char c = keymap[keycode];
        if (c) {
            if (c == '\b' && buffer_index > 0) {
                buffer[--buffer_index] = '\0'; // Borrar el �ltimo car�cter
                print_msg("\b \b", 0x07); // Borrar en pantalla
            } else if (c != '\b' && buffer_index < BUFFER_SIZE - 1) {
                buffer[buffer_index++] = c;
                char str[2] = {c, '\0'};
                print_msg(str, 0x07); // Imprimir el car�cter en la pantalla
            }
        }
    }
}

void init_keyboard() {
    // Registrar el handler de la interrupci�n del teclado
    register_interrupt_handler(KEYBOARD_IRQ, keyboard_handler);
    print_msg("Keyboard handler registered.\n", 0x02);
}

char getchar() {
    if (buffer_index > 0) {
        return buffer[--buffer_index];
    }
    return 0;
}