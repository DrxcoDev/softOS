#ifndef SHELL_H
#define SHELL_H

#define MAX_LINE 1024 //Max lenght of input line
#define MAX_ARGS 64   //Max number of arguments

void print_prompt();
char **parse_line(char *line);
int execute_command(char **args);
void read_line(char *line, int max_length);

#endif 
/*
# SHELL_H
*/
