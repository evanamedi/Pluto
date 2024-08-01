#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include "history.h"

#define BUFFER_SIZE 1024

static struct termios orig_termios;

void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disable_raw_mode);

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON | ISIG);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void clear_line(int position) {
    while (position > 0) {
        printf("\b \b");
        position--;
    }
}

char* read_input() {
    enable_raw_mode();

    int bufsize = BUFFER_SIZE;
    char *buffer = malloc(bufsize);
    if (!buffer) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    int position = 0;
    int history_index = get_history_count();

    while (1) {
        char c = getchar();

        if (c == 4) { // Ctrl+D
            printf("\nExiting shell\n");
            free(buffer);
            disable_raw_mode();
            exit(0);
        }
        if (c == 3) { // Ctrl+C
            printf("\nExiting shell\n");
            free(buffer);
            disable_raw_mode();
            exit(0);
        }

        if (c == '\n') {
            buffer[position] = '\0';
            printf("\n");
            break;
        } else if (c == 127) { // Backspace
            if (position > 0) {
                position--;
                buffer[position] = '\0';
                printf("\b \b");
            }
        } else if (c == '\033') { // Escape sequence
            char seq[3];
            if (read(STDIN_FILENO, &seq[0], 1) != 1) continue;
            if (read(STDIN_FILENO, &seq[1], 1) != 1) continue;
            if (seq[0] == '[') {
                switch (seq[1]) {
                    case 'A': // Up arrow
                        if (history_index > 0) {
                            history_index--;
                            const char *history_command = get_history(history_index);
                            if (history_command) {
                                clear_line(position);
                                strcpy(buffer, history_command);
                                printf("%s", buffer);
                                position = strlen(buffer);
                            }
                        }
                        break;
                    case 'B': // Down arrow
                        if (history_index < get_history_count() - 1) {
                            history_index++;
                            const char *history_command = get_history(history_index);
                            if (history_command) {
                                clear_line(position);
                                strcpy(buffer, history_command);
                                printf("%s", buffer);
                                position = strlen(buffer);
                            }
                        } else if (history_index == get_history_count() - 1) {
                            history_index++;
                            clear_line(position);
                            position = 0;
                        }
                        break;
                    default:
                        break;
                }
            }
        } else {
            buffer[position] = c;
            position++;
            if (position >= bufsize) {
                bufsize += BUFFER_SIZE;
                buffer = realloc(buffer, bufsize);
                if (!buffer) {
                    fprintf(stderr, "Reallocation error\n");
                    exit(EXIT_FAILURE);
                }
            }
            printf("%c", c);
        }
    }

    disable_raw_mode();
    return buffer;
}
