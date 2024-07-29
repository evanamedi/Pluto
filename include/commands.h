#ifndef COMMANDS_H
#define COMMANDS_H

char** parse_command(char *line);
int execute_command(char **args);
int launch_program(char **args);

#endif