#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "commands.h"
#include "builtins.h"

int execute_command(char **args) {
    if (args[0] == NULL) {
        // An empty command was entered
        return 1;
    }

    // Check for built-in commands first
    if (strcmp(args[0], "cd") == 0) {
        return builtin_cd(args);
    } else if (strcmp(args[0], "exit") == 0) {
        return builtin_exit(args);
    } else if (strcmp(args[0], "echo") == 0) {
        return builtin_echo(args);
    } else if (strcmp(args[0], "pwd") == 0) {
        return builtin_pwd(args);
    }

    // If not built-in, launch it as a program
    return launch_program(args);
}

int launch_program(char **args) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            fprintf(stderr, "custom-shell: command not found: %s\n", args[0]);
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Error forking
        perror("fork");
    } else {
        // Parent process
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}