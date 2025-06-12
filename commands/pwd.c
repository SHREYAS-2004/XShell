#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "../terminal.h"

void printWorkingDirectory(char **args){
    char cwd[1024];
    if(getcwd(cwd, sizeof(cwd)) != NULL){
        write(STDOUT_FILENO, cwd, strlen(cwd));
        write(STDOUT_FILENO, "\n", 1);
    }else {
        perror("getcwd");
    }
    
}