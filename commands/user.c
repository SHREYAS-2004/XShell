#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "../terminal.h"

// Used to print the Username
void printUserName(char **args){
    char *username = getlogin();

    // Fallback to environment variable if getlogin fails
    if(!username){
        username = getenv("USER");
    }

    if(username){
        write(STDOUT_FILENO, username, strlen(username));
    }
    else {
        const char *fallback = "Unknown user";
        write(STDOUT_FILENO, fallback, strlen(fallback));
    }
    write(STDOUT_FILENO, "\n", 1);
}