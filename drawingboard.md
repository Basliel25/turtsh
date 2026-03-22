## A shell does
1. *Initialize* - A typical shell would initialize and read configuration files, that would change how the shell beahvious.
    - [ ] Define Behaviours/Aspects
        - [ ] Path handling
2. *Interpret* - the shell reads command from `stdin` (could be *interactive, file*).
    - [x] Accept inputs
        - [ ] Accept Batch inputs
    - [x] Tokenize and return a null terminated array of pointers to each tokens
    - [x] Fork processes and Handle hierarchy
    - [x] Execute with appropriate commands
3. *Terminate* - Cleans up and exits
    - [ ] Shutdown commands
    - [ ] Frees up memory
    - [ ] Terminates 

## The basic loop of the shell
1. *Read* -  accepts the commands 
2. *Separates* - Tokenize input into command and arguments
3. *Execute* - run the command with the appropriate commands

## Core Architecture
##### - Initialize 
    - Initialize the shell with an path including /bin - `void turtsh_init();` 
    - The path - `char **shell_path;`
    - The path count - `int path_s;` 
##### - Read command from input
    - Reads lines using `fgetc` and returns char array with dynamic memory - `char *turtsh_read();`
##### - Tokenize arguments
    - Splits the prompt with delimeters, returns array of pointers to tokenized elements of the prompt - `PLine turtsh_split(char *prompt);`
    - Seprate parallel commands into ParsedLine 
        ```C
        typedef sruct {
            Command *commands;
            int commands;
            int command_s; //Command size
        } PLine    
        ```
    - Each command is a variable with related arguments and a redirection path
        `typedef struct {
            char **arguments;
            char *redirect_path // points to NULL if no redirection;
         } Command`

##### - Helper Functions
    - Split using a delimeter, returns array of tokens. 
    ```C
    char **split_delimeter(char *prompt, char *delimeter, int *count);
    ```
    - Extract redirection, returns the filename or NULL if not file name.
    ```C
    char *extract_redirect(char **args); 
    ```
    - Write the output of the command to the redirected file
    ```C
    void redirect_output(Stringhh
    ```


##### - Run 
    - Excute each command of PLine
        - If command has redirection 
            - Create a file descriptor `fd` for the output file
            - Attach stdout to `fd`
        - Execute commands with each arguments
    - Clean up memory and prepare for next prompt

- Builtin Functions
Define builtin functions that cant be directly forked as a child process
`int ls_cd(Command command);`
`int ls_exit(Command command);`
`int ls_cd(**arguments);`
`int path(**arguments);`


## File Orgnaization
turtsh/
|-- builtin.c
|-- builtin.h
|-- turtsh.c
|-- main.c
|-- turtsh.h
|-- README
|-- Makefile

