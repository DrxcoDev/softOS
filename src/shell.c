#include "../include/shell.h"
#include "../include/print.h"
#include "../include/io.h"
#include "../include/keyboard.h"
#include <stddef.h>
#include <string.h>

void print_prompt() {
    print_msg("> ", 0x07);
}

char* read_line() {
    static char line[256];
    int index = 0;
    char c;

    while (1) {
        c = getchar();
        if (c) {  // Solo procesar si c no es 0
            if (c == '\n' || c == '\r') {
                line[index] = '\0';
                print_msg("\n", 0x07);
                return line;
            } else if (c == '\b' && index > 0) {
                index--;
                print_msg("\b \b", 0x07);  // Borra el �ltimo car�cter en la pantalla
            } else if (c != '\b') {
                line[index++] = c;
                char str[2] = {c, '\0'};
                print_msg(str, 0x07);  // Imprime el car�cter en la pantalla
            }
        }
    }
}

char** parse_line(char* line) {
    static char* args[2];
    args[0] = line;
    args[1] = NULL;
    return args;
}

int execute_command(char** args) {
    if (args[0] != NULL) {
        print_msg("Executing command: ", 0x07);
        print_msg(args[0], 0x07);
        print_msg("\n", 0x07);
    }
    return 1;  // Retorna 1 para continuar el loop de la shell
}