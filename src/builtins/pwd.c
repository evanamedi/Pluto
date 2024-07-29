#include <stdio.h>
#include <unistd.h>
#include "builtins.h"

int builtin_pwd(char **args) {
	(void)args;
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("%s\n", cwd);
	} else {
		perror("pwd");
	}
	return 1;
}
