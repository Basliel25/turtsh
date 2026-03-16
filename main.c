#include "turtsh.h"
#include "builtins.h"

int main() {
    printf("Turtshell Started\n");
    char *line = turtsh_read();
    printf("Input was: %s", line);
    char **tokens = turtsh_split(line);
    for (int i = 0; tokens[i] != NULL; i++) {
    printf("%s\n", tokens[i]);
}
    free(line);
    return 0;
}
