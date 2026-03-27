#include "parser.h"

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
            tokens = realloc(tokens, size_of_tokens);
        }
    }

    tokens[token_s] = '\0';

    return tokens; 
}

char *extract_redirect(char **args); 
