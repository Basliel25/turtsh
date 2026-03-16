## A shell does
1. *Initialize* - A typical shell would initialize and read configuration files, that would change how the shell beahvious.
    - [ ] Define Behaviours/Aspects
    - [ ]  
2. *Interpret* - the shell reads command from `stdin` (could be *interactive, file*).
    - [ ] Accept inputs
    - [ ] Tokenize and return a null terminated array of pointers to each tokens
    - [ ] Fork processes and Handle hierarchy
    - [ ] Execute with appropriate commands
3. *Terminate* - Cleans up and exits
    - [ ] Shutdown commands
    - [ ] Frees up memory
    - [ ] Terminates 

## The basic loop of the shell
1. *Read* -  accepts the commands from `stdin`
2. *Separates* - Breaks down the command passed into *program calls* and *arguments to programs*
3. *Execute* - run the command with the appropriate commands

## Core Architecture
- Initialize
`void turtsh_init();`
- Read raw input from `stdin`
`char *turtsh_read();`
- Tokenize arguments
`char **turtsh_split(char *prompt);`
- Run 
`int turtsh_execute(**arguments);`
- Builtin Functions
Define builtin functions that cant be directly forked as a child process
`int ls_cd(**arguments);`
`int ls_exit(**arguments);`
`int ls_cd(**arguments);`


## File Orgnaization
turtsh/
|-- builtin.c
|-- builtin.h
|-- turtsh.c
|-- main.c
|-- turtsh.h
|-- README
|-- Makefile
