#include "../terminal.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void printFileDetails(const char *path, struct dirent *entry){
    char fullPath[1024];

    size_t path_len = strlen(path);
    if(path[path_len - 1] == '/'){
        snprintf(fullPath, sizeof(fullPath), "%s%s", path, entry->d_name);
    }else{
        snprintf(fullPath, sizeof(fullPath), "%s/%s", path, entry->d_name);
    }
    

    struct stat fileStat;
    if(stat(fullPath, &fileStat) == -1){
        perror("stat");
        return;
    }

    // File type and permissions
    char perms[11] = "----------";
    if(S_ISDIR(fileStat.st_mode)) perms[0] = 'd';
    else if(S_ISLNK(fileStat.st_mode)) perms[0] = 'l';
    else if(S_ISCHR(fileStat.st_mode)) perms[0] = 'c';
    else if(S_ISBLK(fileStat.st_mode)) perms[0] = 'b';
    else if(S_ISFIFO(fileStat.st_mode)) perms[0] = 'p';
    else if(S_ISSOCK(fileStat.st_mode)) perms[0] = 's';

    if(fileStat.st_mode & S_IRUSR) perms[1] = 'r';
    if(fileStat.st_mode & S_IWUSR) perms[2] = 'w';
    if(fileStat.st_mode & S_IXUSR) perms[3] = 'x';
    if(fileStat.st_mode & S_IRGRP) perms[4] = 'r';
    if(fileStat.st_mode & S_IWGRP) perms[5] = 'w';
    if(fileStat.st_mode & S_IXGRP) perms[6] = 'x';
    if(fileStat.st_mode & S_IROTH) perms[7] = 'r';
    if(fileStat.st_mode & S_IWOTH) perms[8] = 'w';
    if(fileStat.st_mode & S_IXOTH) perms[9] = 'x';

    // Owner and group
    struct passwd *pw = getpwuid(fileStat.st_uid);
    struct group *gr = getgrgid(fileStat.st_gid);

    // Time
    char timebuf[64];
    strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&fileStat.st_mtime));

    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%s %2ld %s %s %8ld %s %s\n",
        perms,
        (long)fileStat.st_nlink,
        pw ? pw->pw_name : "unknown",
        gr ? gr->gr_name : "unknown",
        (long)fileStat.st_size,
        timebuf,
        entry->d_name
    );
    write(STDOUT_FILENO, buffer, strlen(buffer));

}

void listDirectory(char **args){
    //system("ls");
    const char *path = "."; // Default: current directory 
    int showAll = 0; // -a
    int longList = 0; // -l
    int pathset = 0;

    //Parse flags and path
    for(int i=1; args[i] != NULL; i++){
        if(args[i][0] == '-'){
            if(strchr(args[i], 'a')) showAll = 1;
            if(strchr(args[i], 'l')) longList = 1;
        }
        else if(!pathset){
            path = args[i]; // Assume it's a path
            pathset = 1;
        }
    }


    DIR *dir = opendir(path);
    if(dir == NULL){
        char errMsg[256];
        snprintf(errMsg, sizeof(errMsg), "ls: cannot access %s : %s\n", path, strerror(errno));
        write(STDOUT_FILENO, errMsg, strlen(errMsg));
        return;
    }

    struct dirent *entry;
    while((entry = readdir(dir)) != NULL){
        // Skip hidden files (those starting with '.')
        if(!showAll && entry->d_name[0] == '.'){
            continue;
        }
        
        if(longList){
            printFileDetails(path, entry);
        }else {
            write(STDOUT_FILENO, entry->d_name, strlen(entry->d_name));
            write(STDOUT_FILENO, "  ", 2); // Space between entries;
        }
    }

    if(!longList){
        write(STDOUT_FILENO, "\n", 1); //Newline at the end
    }
    
    closedir(dir);
}

