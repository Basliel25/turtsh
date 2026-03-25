#include "turtsh.h"

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

char **turtsh_split(char *prompt) {

    // Initialize dynamic memory space
    // Initial capacity: 8 chars
    int size_of_tokens = 8;
    char **tokens = malloc(size_of_tokens * (sizeof(char *))); 

    // Strtok to tokenize with the delimeters:
    // - '\t' tab
    // - ' ' space
    // - '\n' new line
    int token_s = 0;
    char *tokenized = strtok(prompt, "\t\n ");

    // Assign tokenized chars to storage
    while(tokenized != NULL) {
       tokens[token_s] = tokenized;
       token_s++;
       tokenized = strtok(NULL, "\t\n "); 

       // Handle buffer overflow
       // Double size of tokens when full
       if(token_s >= size_of_tokens) {
            size_of_tokens *= 2;
            tokens = realloc(tokens, size_of_tokens * (sizeof(char *)));
       }
    }
    // Add null to the end of tokens
    tokens[token_s] = '\0';
    return tokens;
}

int turtsh_execute(char **arguments) {

    // The process id of the child fork
    pid_t pid = fork();

    if(pid == 0) {
        execvp(arguments[0], arguments);
        //If execvp failed
        perror("Process failed");
        exit(1);
    } else if(pid > 0) {
        waitpid(pid, NULL, 0);
    } else
        printf("Fork failed");
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
        char **arguments = turtsh_split(prompt);
        // Execute arguments
        turtsh_execute(arguments);
        printf("________________________________\n");
   } 
}
