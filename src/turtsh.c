#include "turtsh.h"
#include "Parser/parser.h"
#include "builtins.h"
#include <unistd.h>

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

    PLine PLine; 

    int size_of_commands = 8;
    Command *parsed_commands = malloc(size_of_commands * (sizeof(Command)));
    int command_count = 0;

    // Split multiple commands
    char *delimeter = "&";
    char **tok_commands = split_delimeter(prompt, delimeter);

    // Example input: 
    // "ls -l & cd here & ls -a & echo "despair" > output.txt"
    while(tok_commands[command_count] != NULL) {
        
        Command current_command;
        char *command = (tok_commands[command_count]);

        // Check for redirect in command
        if(has_redirect(command)) {
            // Split, extract, attach redirect to interface
            current_command.redirect = extract_redirect(command);
            if(current_command.redirect == NULL) {
                printf("\nInvalid Redirect\n");
                current_command.redirect = NULL;
            } 
        } else  
                current_command.redirect = NULL;
        
        // Tokenize for args using ' \t' as delimeter
        int arg_count = 0;
        int arg_s = 8;
        delimeter = " \t";
        current_command.args = malloc(size_of_commands * (sizeof(char *)));

        // Extracts each command and argument
        char **command_args = split_delimeter(command, delimeter);
        // Set up args in command array for each command in Pline
        while(command_args[arg_count] != NULL) {
            current_command.args[arg_count] = command_args[arg_count];
            arg_count++;

            if(arg_count >= arg_s) {
                arg_s *= 2;
                current_command.args = realloc(current_command.args, arg_s * (sizeof(char *)));
            }
        }
        current_command.args[arg_count] = '\0';
        // Add this constructed command to PLine
        if(size_of_commands >= command_count) {
            size_of_commands *= 2;
            parsed_commands = realloc(parsed_commands, size_of_commands * (sizeof(char *)));
        }
        parsed_commands[command_count] = current_command;
        // Increase command_count
        command_count++;
        // Continue with next command, if it doesnt exist loop terminates
    }

    PLine.command = parsed_commands;
    PLine.count = command_count;
    PLine.capacity = size_of_commands;

    return PLine;
}

int turtsh_execute(PLine PLine) {


    // Access Parsed Line
    int command_count = PLine.count;

    // Loop over all commands in PLine.commands
    for(int i = 0; i < command_count; i++) {
        // Handle  CD and exit
        Command current_command = PLine.command[i];
        if(strcmp(current_command.args[0], "cd") == 0) {
            turtsh_cd(current_command.args[1]);
            continue;
        } else if(strcmp(current_command.args[0], "exit") == 0) {
            turtsh_exit();
        }

        // The process id of the child fork
        pid_t pid = fork();
        if(pid == 0) {
            if(current_command.redirect != NULL) {
                // Redirect Stdout to file
                printf("Redirect for %s: %s\n", current_command.args[0], current_command.redirect);
                int fd = open(current_command.redirect, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if(fd == -1) {
                    perror("File redirection failed");
                    exit(1);
                }
                dup2(fd, 1);
                close(fd);
            }
            execvp(current_command.args[0], current_command.args);
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
