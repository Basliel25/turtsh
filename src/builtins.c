#include "builtins.h"
#include "turtsh.h"

int turtsh_cd(char *path) {return chdir(path);}
void turtsh_exit() {exit(1);}
