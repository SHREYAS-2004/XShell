#include "../terminal.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>


// Used to toggle using "cd -"
char prev_dir[4096] = {0};

void changeDirectory(char **args){
    char cwd[4096];
    
    if(getcwd(cwd,sizeof(cwd)) == NULL){
        perror("getcwd");
        return;
    }

    int result;

    // Change directory to home using "cd" or "cd ~";
    if(args[1] == NULL || strcmp(args[1], "~") == 0){
        char *home = getenv("HOME");
        if(home != NULL){
            result = chdir(home);
            if (result == -1){
                perror("cd");
                return;
            }
        } else{
            const char *msg = "cd: HOME environment variable not set\n";
            write(STDOUT_FILENO, msg, strlen(msg));
            return;
        }
    } 
    
    // Toggle the directory with previous working directory "cd -"
    else if( strcmp(args[1],"-") == 0){
        // Go to previous directory (saved in prev_dir)
        if(prev_dir[0] == '\0') {
            const char *msg = "cd: OLDPWD not set\n";
            write(STDOUT_FILENO, msg, strlen(msg));
            return;
        }
        result = chdir(prev_dir);
        if( result == -1){
            perror("cd");
            return;
        }

        // Print the directory we just switched to
        write(STDOUT_FILENO, prev_dir, strlen(prev_dir));
        write(STDOUT_FILENO, "\n", 1);
    } 
    
    // Change the directory with respect to home directory "cd ~/path"
    else if (args[1][0] == '~'){
        // Expand ~ manually
        char *home = getenv("HOME");
        if(home != NULL){
            char fullPath[4096];
            snprintf(fullPath, sizeof(fullPath), "%s%s", home, args[1]+1);
            result = chdir(fullPath);
            if(result == -1){
                char errMsg[4096];
                snprintf(errMsg, sizeof(errMsg), "cd: %.4000s: %s\n", fullPath, strerror(errno));
                write(STDOUT_FILENO, errMsg, strlen(errMsg));
                return;
            }
        } else {
            const char *msg = "cd: HOME environment variable not set\n";
            write(STDOUT_FILENO, msg, strlen(msg));
            return;
        }

    } 
    
    // Change directory with respect to present working directory "cd <path>"
    else{
        result = chdir(args[1]);
        if(result == -1){
            // error if path doesn't exist
            char errMsg[4096];
            snprintf(errMsg, sizeof(errMsg), "cd: %.4000s: %s\n", args[1], strerror(errno));
            write(STDOUT_FILENO, errMsg, strlen(errMsg));
            return;
        }
    }

    // If directory change was successfull, Save the current directory as previous directory for next use
    strncpy(prev_dir, cwd, sizeof(prev_dir));
    prev_dir[sizeof(prev_dir) - 1] = '\0';
}