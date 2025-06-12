#include "terminal.h"
#include <pwd.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>  // for PATH_MAX


// ANSI escape codes for colors
#define RESET   "\x1b[0m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define RED     "\x1b[31m"

int main() {
    char input[MAX_INPUT];
    char cwd[PATH_MAX];
    char username[256];
    char hostname[256];

    enableRawMode();

    while(1) {
        // Get current working directory
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            strcpy(cwd, "?");
        }

        // Get username
        struct passwd *pw = getpwuid(getuid());
        if (pw) {
            strncpy(username, pw->pw_name, sizeof(username));
            username[sizeof(username) - 1] = '\0';
        } else {
            strcpy(username, "unknown");
        }

        // Get hostname
        if (gethostname(hostname, sizeof(hostname)) != 0) {
            strcpy(hostname, "unknown");
        }

        // Print prompt with colors
        printf(RED "MyShell>" GREEN "%s@%s:" BLUE "%s" RESET "$ " , username, hostname, cwd);
        fflush(stdout);

        readLine(input, MAX_INPUT);

        if(strcmp(input, "exit") == 0)
            break;

        parseAndExecute(input);
    }

    return 0;
}
