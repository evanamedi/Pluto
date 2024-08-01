#include "history.h"
#include <stdlib.h>
#include <string.h>

#define HISTORY_SIZE 100

static char *history[HISTORY_SIZE];
static int history_count = 0;

void init_history() {
    for (int i = 0; i < HISTORY_SIZE; i++) {
        history[i] = NULL;
    }
}

void add_history(const char *command) {
    if (history[history_count % HISTORY_SIZE]) {
        free(history[history_count % HISTORY_SIZE]);
    }
    history[history_count % HISTORY_SIZE] = strdup(command);
    history_count++;
}

const char* get_previous_command() {
    static int history_index = 0;
    if (history_index > 0) {
        history_index--;
        return history[history_index % HISTORY_SIZE];
    }
    return NULL;
}

const char* get_next_command() {
    static int history_index = 0;
    if (history_index < history_count) {
        history_index++;
        return history[history_index % HISTORY_SIZE];
    }
    return NULL;
}

int get_history_count() {
    return history_count;
}

const char* get_history(int index) {
    if (index >= 0 && index < history_count) {
        return history[index % HISTORY_SIZE];
    }
    return NULL;
}
