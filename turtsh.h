#ifndef TURTSH
#define TURTSH
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct {
   char **args;
   char *redirect;
} Command;

typedef struct {
    Command *command;
    int *count;
    int *capacity;
} PLine;

void turtsh_init();
char *turtsh_read();
PLine **turtsh_split(char *prompt);
int turtsh_execute(PLine parsed_line);

char **split_delimeter(char *prompt, char *delimeter, int *count);
#endif
