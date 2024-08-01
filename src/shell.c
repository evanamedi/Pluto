#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <signal.h>
#include "shell.h"
#include "commands.h"
#include "history.h"
#include "input.h"

#define RESET_COLOR "\033[0m"
#define PROMPT_COLOR "\033[1;32m"

void handle_signal(int signal) {
    if (signal == SIGINT) {
        printf("\nExiting shell\n");
        disable_raw_mode();  // Ensure raw mode is disabled before exiting
        exit(0);
    }
}

void init_shell() {
    printf("Welcome to Custom Shell!\n");
    init_history();
    signal(SIGINT, handle_signal);
}

void run_shell() {
    char *line;
    char cwd[PATH_MAX];
    while (1) {
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf(PROMPT_COLOR "%s > " RESET_COLOR, cwd);
        } else {
            perror("getcwd");
            exit(EXIT_FAILURE);
        }
        line = read_input();
        if (line && *line) {
            add_history(line); // Add the command to history
            execute_line(line);
            free(line);
        }
    }
}

void execute_line(char *line) {
    char **args = parse_command(line);
    if (args == NULL) {
        fprintf(stderr, "custom-shell: parsing error\n");
        return;
    }
    if (execute_command(args) == -1) {
        perror("custom-shell");
    }
    free(args);
}
