#include "../include/io.h"  // Asegúrate de incluir el archivo de cabecera
#include "../include/keyboard.h"

char get_input_keycode(void) {
    unsigned char keycode;
    while ((keycode = inb(KEYBOARD_PORT)) == 0);
    return keycode;
}
