#include "../include/io.h"  // Asegúrate de incluir el archivo de cabecera
#include "../include/keyboard.h"
#include "../include/print.h"
#include "../include/interrupts.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_IRQ 1

static char keymap[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z',
    'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3',
    '0', '.'
};

static char buffer = 0;

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

        buffer = keymap[keycode];
    }
}

void init_keyboard() {
    // Registrar el handler de la interrupci�n del teclado
    register_interrupt_handler(KEYBOARD_IRQ, keyboard_handler);
}

char getchar() {
    char c = buffer;
    buffer = 0; // Limpiar el buffer despu�s de leer
    return c;
}
