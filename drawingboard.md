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
- Initialize 
    - Initialize the shell with an path including /bin - `void turtsh_init();` 
    - The path - `char **shell_path;`
    - The path count - `int path_s;` 
- Read command from input
    - Reads lines using `fgetc` and returns char array with dynamic memory - `char *turtsh_read();`
- Tokenize arguments
    - Splits the prompt with delimeters, returns array of pointers to tokenized elements of the prompt - `Command turtsh_split(char *prompt);`
    - Retrun a command struct with redirection
        `typedef struct {
            char **arguments;
            char *redirect_path // points to NULL if no redirection;
         } Command`
- Run 
    - If command has redirection 
    - Execute command along with path using `execv()` library - `int turtsh_execute(Command command);`
- Builtin Functions
Define builtin functions that cant be directly forked as a child process
`int ls_cd(**arguments);`
`int ls_exit(**arguments);`
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
