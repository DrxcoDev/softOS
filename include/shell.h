#ifndef SHELL_H
#define SHELL_H

#define MAX_LINE 1024 //Max lenght of input line
#define MAX_ARGS 64   //Max number of arguments

char simple_getchar(); // Declaraci�n de la funci�n simple_getchar

void print_prompt();
char* read_line();
char** parse_line(char* line);
int execute_command(char** args);

#endif 
/*
# SHELL_H
*/
