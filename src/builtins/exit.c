#include <stdlib.h>
#include "builtins.h"

int builtin_exit(char **args) {
    (void)args;
    exit(0);
}