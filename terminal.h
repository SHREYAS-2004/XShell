#ifndef TERMINAL_H
#define TERMINAL_H

#ifdef MAX_INPUT
#undef MAX_INPUT
#endif
#define MAX_INPUT 4096

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<termios.h>
#include<string.h>

void enableRawMode();
void disableRawMode();
void readLine(char * buffer, int size);
void parseAndExecute(char * input);
void executeCommand(char ** args);

void changeDirectory(char **args);
void listDirectory(char **args);
void echoInput(char **args);
void printWorkingDirectory(char **args);
void printUserName(char **args);
void makeDirectory(char **args);
void removeDirectory(char **args);


#endif