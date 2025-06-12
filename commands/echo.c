#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "../terminal.h"

void echoInput(char **args){
    for(int i=1; args[i] != NULL; i++){
        write(STDOUT_FILENO, args[i], strlen(args[i]));
        write(STDOUT_FILENO, " ", 1);
    }
    write(STDOUT_FILENO, "\n", 1);
}