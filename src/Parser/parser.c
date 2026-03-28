#include "parser.h"
#include <stdbool.h>

char **split_delimeter(char *prompt, char *delimeter) {
    // Initialize dynamic memory space
    // Initial capacity: 8 chars
    int size_of_tokens = 8;
    char **tokens = malloc(size_of_tokens * (sizeof(char *))); 

    // Track token capacity of capacity
    // Tokenize char array with appropriate delimeters
    int token_s = 0;
    char *tokenized = strtok(prompt, delimeter);

    while(tokenized != NULL) {
        tokens[token_s] = tokenized;
        token_s++;
        tokenized = strtok(NULL, delimeter);

        // Dynamic resizing to
        // handle buffer overflow
        if(token_s >= size_of_tokens) {
            size_of_tokens *= 2;
            tokens = realloc(tokens, size_of_tokens * sizeof(char *));
        }
    }

    tokens[token_s] = NULL;

    return tokens; 
}
char *extract_redirect(char *command) {
    // Handle multiple redirects
    char *redirect = '\0';
    int redirect_count = 0;
    // Parse the command with redirect
    // While *command is not NULL, *command++
    while(*command != '\0') {
        if(*command == '>') {
            redirect_count++;
            if(redirect_count > 1)
                return NULL;
            *command = '\0';
            redirect = command + 1;
            while((*redirect == ' ' || *redirect == '\t') && *redirect != '\0') {
                redirect++;
            }
            if(*redirect == '\0')
                return NULL;
        }
        command++;
    }
    return redirect;
} 

bool has_redirect(char *line){
    int iterate = 0;
    while(line[iterate] != '\0') {
        if(line[iterate] == '>')
            return true;
        iterate++;
    }
    return false;
}
