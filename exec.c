#include "terminal.h"

void executeCommand(char **args){
    if(args[0] == NULL)
        return;

    if(strcmp(args[0], "cd") == 0){
        changeDirectory(args);
    }else if(strcmp(args[0],"ls") == 0){
        listDirectory(args);
    } else if(strcmp(args[0], "echo") == 0){
        echoInput(args);
    } else if (strcmp(args[0], "pwd") == 0){
        printWorkingDirectory(args);
    } else if (strcmp(args[0], "whoami") == 0){
        printUserName(args);
    } else{
        write(STDOUT_FILENO, "Unknown command\n", 17);
    }
}