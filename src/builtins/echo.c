#include <stdio.h>
#include "builtins.h"

int builtin_echo(char **args) {
	for (int i = 1; args[i] != NULL; i++) {
		printf("%s ", args[i]);
	}
	printf("\n");
	return 1;
}
