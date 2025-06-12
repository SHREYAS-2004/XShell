#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include "../terminal.h"

void makeDirectory(char **args){

    if(args[1] == NULL){
        const char *msg = "mkdir: missing operand\n";
        write(STDOUT_FILENO, msg, strlen(msg));
        return;
    }

    if(mkdir(args[1], 0755) == -1){
        
        char errMsg[256];
        snprintf(errMsg, sizeof(errMsg), "mkdir: cannot create directory %s : %s\n", args[1], strerror(errno));
        write(STDOUT_FILENO, errMsg, strlen(errMsg));
    }
    else{

        char successMsg[256];
        snprintf(successMsg, sizeof(successMsg), "Directory %s created successfully\n", args[1]);
        write(STDOUT_FILENO, successMsg, strlen(successMsg)); 
    }
}