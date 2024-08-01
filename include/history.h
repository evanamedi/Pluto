#ifndef HISTORY_H
#define HISTORY_H

void init_history();
void add_history(const char *command);
const char* get_previous_command();
const char* get_next_command();
int get_history_count();       // Getter for history count
const char* get_history(int index); // Getter for history command by index

#endif // HISTORY_H
