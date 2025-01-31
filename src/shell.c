#include "../include/shell.h"
#include "../include/print.h"
#include "../include/io.h"
#include "../include/keyboard.h"
#include <stddef.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 256

void print_prompt() {
    print_msg("> ", COLOR_WHITE);
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

void read_line(char *line, int max_length) {
    int i = 0;
    while (i < max_length - 1) {
        char c = getchar();
        if (c) {
            if (c == '\n' || c == '\r') {
                break;
            }
            line[i++] = c;
            char str[2] = {c, '\0'};
            print_msg(str, 0x07); // Usar el color blanco para el texto ingresado
        }
    }
    line[i] = '\0'; // Terminar la l�nea con un car�cter nulo
}