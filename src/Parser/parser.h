/**
 * @file    builtins.h
 * @brief   Built-in commands for TurtShell
 * @author  Your Name
 * 
 * Interfaces multiple tools to refine raw commands 
 * into prgogram acceptable format.
 */
#ifndef PARSER
#define PARSER
#include "../turtsh.h"

/**
 * @brief Splits a string with a given delimeter returns array of pointers
 * @param char *prompt Pointer to the string to be split
 * @param char *delimeter separator to tokenize commands
 * @param int *count of commands within a string
 * @return char **array of pointers to tokenized strings
 */
char **split_delimeter(char *prompt, char *delimeter);

/**
 * @brief Extracts a redirection command 
 * @param char **args tokenized commands
 * @return char *redirect the string containg the redirect destination
 *          NULL if no redirects
 */
char *extract_redirect(char *args); 

bool has_redirect(char *line);
#endif
