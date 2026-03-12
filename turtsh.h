#ifndef TURTSH
#define TURTSH
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void turtsh_init();
char *turtsh_read();
char **turtsh_split(char *prompt);
int turtsh(char **arguments);

#endif
