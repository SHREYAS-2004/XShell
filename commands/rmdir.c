#include "../terminal.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void removeDirectory(char **args){
    if(args[1] == NULL){
        const char *msg = "rmdir: missing operand\n";
        write(STDOUT_FILENO, msg, strlen(msg));
        return;
    }

    for(int i=1; args[i] != NULL; i++){
        if(rmdir(args[i]) == -1){
            char errMsg[256];
            snprintf(errMsg, sizeof(errMsg), "rmdir: failed to remove '%s': %s\n", args[i], strerror(errno));
            write(STDOUT_FILENO, errMsg, strlen(errMsg));
        } else {
            char successMsg[256];
            snprintf(successMsg, sizeof(successMsg), "Directory '%s' removed sucessfully\n", args[i]);
            write(STDOUT_FILENO, successMsg, strlen(successMsg));
        }
    }
}