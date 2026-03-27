#include "turtsh.h"
#include "Parser/parser.h"

char *turtsh_read(){

   char *prompt = malloc(128); 
   char *buf = prompt;
   int c;

   char cwd[1024];
   getcwd(cwd,sizeof(cwd));
   printf("(turtsh in %s)>", cwd);
   while(((c = fgetc(stdin)) != '\n') && c != EOF) {
       // Keep reading char from fgetc and appending to buffer
        *prompt++ = c;

        //Handle buffer overflow
        int position = prompt - buf;
        if(position >= 128) 
            prompt = realloc(prompt, strlen(buf)*2);
   }
   //Assign Null value to end
   *prompt = '\0';
   return buf;
}

PLine turtsh_split(char *prompt) {

    int size_of_commands = 8;
    PLine command; 

    return command;
}

int turtsh_execute(PLine PLine) {

    // The process id of the child fork
    pid_t pid = fork();

    // Access Parsed Line
    int command_count = (int) PLine.count;
    Command *commands = PLine.command;

    // Loop over all commands in PLine.commands
    for(int i = command_count; i > 0; i--) {
        char **command = commands[command_count - i].args;

        if(pid == 0) {
            execvp(command[0], command);
            //If execvp failed
            perror("Process failed");
            exit(1);
        } else if(pid > 0) {
            waitpid(pid, NULL, 0);
        } else
            printf("Fork failed");
    }
    return 0; 
}

void turtsh_init() {
   while(1) {
        char *prompt = turtsh_read();

        if(prompt == NULL) {
            printf("No input detected\n");
            continue;
        }

        // Tokenize input into arguments
        PLine parsed_line = turtsh_split(prompt);
        // Execute arguments
        turtsh_execute(parsed_line);
        printf("________________________________\n");
   } 
}
