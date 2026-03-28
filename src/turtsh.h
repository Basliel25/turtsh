#ifndef TURTSH
#define TURTSH
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * @brief a single command with potential redirect path
 */
typedef struct {
   char **args; /**< NULL-terminated argument vector*/
   char *redirect; /**< Path to redirect NULL if not provided or on invalid input*/
} Command;

/**
 * @brief A complete parsed input organized and tokenized into commands, args, and redirects
 */
typedef struct {
    Command *command; /**< NULL-terminated Command vector*/
    int count; /**< Number of commands */ 
    int capacity; /**< Memory size of commands vector */
} PLine;

/**
 * @brief Initalize the core logic of the program, continues to loop until exited
 */
void turtsh_init();

/**
 * @brief Reads input from Stdin
 * @return char * array pointing to the user inputed string.
 */
char *turtsh_read();

/**
 * @brief Parses command and uses helper functions to organize user input into commands and args
 * @param char *prompt input by user
 * @return PLine a struct with all commands and number of commands
 */
PLine turtsh_split(char *prompt);

/**
 * @brief Organize PLine into child process to sequentially execute
 * @param PLine tokenized and organized commands
 * @return int exit status
 */
int turtsh_execute(PLine parsed_line);

#endif
