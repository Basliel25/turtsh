#include "turtsh.h"
#include "builtins.h"

int main() {
    printf("Turtshell Started\n");
    char *line = turtsh_read();
    printf("Input was: %s", line);
    free(line);
    return 0;
}
