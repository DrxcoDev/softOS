#ifndef SHELL_H
#define SHELL_H

void print_prompt();
char **parse_line(char *line);
int execute_command(char **args);
void read_line(char *line, int max_length);

#endif // SHELL_H