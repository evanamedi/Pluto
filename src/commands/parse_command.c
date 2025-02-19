#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "commands.h"

#define TOKEN_BUFSIZE 64
#define TOKEN_DELIM " \t\r\n\a"

char** parse_command(char *line) {
	int bufsize = TOKEN_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if (!tokens) {
		fprintf(stderr, "allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, TOKEN_DELIM);
	while (token != NULL) {
		tokens[position] = token;
		position++;

		if (position >= bufsize) {
			bufsize += TOKEN_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens) {
				fprintf(stderr, "allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, TOKEN_DELIM);
	}
	tokens[position] = NULL;
	return tokens;
}
