#include "terminal.h"

void parseAndExecute(char *input) {
    char *args[64];
    int i = 0;
    char *token = strtok(input, " ");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
    executeCommand(args);
}

void readLine(char *buffer, int size) {
    int i = 0;
    char c;
    while (i < size - 1) {
        if (read(STDIN_FILENO, &c, 1) == 1) {
            if (c == '\n') {
                buffer[i] = '\0';
                write(STDOUT_FILENO, "\n", 1);
                break;
            } else if (c == 127 || c == '\b') {
                if (i > 0) {
                    i--;
                    write(STDOUT_FILENO, "\b \b", 3);
                }
            } else {
                buffer[i++] = c;
                write(STDOUT_FILENO, &c, 1);
            }
        }
    }
    buffer[i] = '\0';
}
