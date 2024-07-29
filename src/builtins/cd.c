#include <stdio.h>
#include <unistd.h>
#include "builtins.h"

int builtin_cd(char **args) {
	if (args[1] == NULL) {
		fprintf(stderr, "custom-shell: expected argument to \"cd\"\n");
	} else {
		if (chdir(args[1]) != 0) {
			perror("custom-shell");
		}
	}
	return 1;
}
