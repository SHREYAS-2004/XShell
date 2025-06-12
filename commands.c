#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "terminal.h"

void changeDirectory(char **args){
    if(args[1] == NULL){
        char *home = getenv("HOME");
        if(home != NULL){

            chdir(home);
        }
    }else if(strcmp(args[1], "..") == 0){
        // cd ..
        chdir("..");
    }else{
        chdir(args[1]);
    }
}

void listDirectory(char **args){
    system("ls");
}

void echoInput(char **args){
    for(int i=1; args[i] != NULL; i++){
        write(STDOUT_FILENO, args[i], strlen(args[i]));
        write(STDOUT_FILENO, " ", 1);
    }
    write(STDOUT_FILENO, "\n", 1);
}

void printWorkingDirectory(char **args){
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    write(STDOUT_FILENO, cwd, strlen(cwd));
    write(STDOUT_FILENO, "\n", 1);
}

void printUserName(char **args){
    char *username = getenv("USER");
    if(username){
        write(STDOUT_FILENO, username, strlen(username));
    }
    write(STDOUT_FILENO, "\n", 1);
}