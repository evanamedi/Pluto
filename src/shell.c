#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include "shell.h"
#include "commands.h"

#define RESET_COLOR "\033[0m"
#define PROMPT_COLOR "\033[1;32m"

void init_shell() {
	printf("Welcome to Custom Shell\n");
}

void run_shell() {
	char *line;
	char cwd[PATH_MAX];
	while (1) {
		if (getcwd(cwd, sizeof(cwd)) != NULL) {
			printf(PROMPT_COLOR "custom-shell> " RESET_COLOR);	
		} else {
			perror("getcwd");
			exit(EXIT_FAILURE);
		}
		line = read_line();
		if (line == NULL) {
			break;
		}
		execute_line(line);
		free(line);
	}
}

char* read_line() {
	char *line = NULL;
	size_t len = 0;
	if (getline(&line, &len, stdin) == -1) {
		if (feof(stdin)) {
			exit(0);
		} else {
			perror("readline");
			exit(1);
		}
	}
	return line;
}

void execute_line(char *line) {
	char **args = parse_command(line);
	if (args == NULL) {
		fprintf(stderr, "custom-shell: parsing error\n");
	}
	if (execute_command(args) == -1) {
		perror("custom-shell");
	}
	free(args);
}
