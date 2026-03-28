# TurtShell
---
# turtsh

A Simple toy UNIX shell implementation in C.
## Features
- Command execution via `fork`/`execvp`
- Output redirection (`>`)
- Parallel command execution (`&`)
- Built-in commands: `cd`, `exit`

## Build

```bash
make clean
```

## Run

```bash
make run
```

## Test

```bash
make test
```

## Docs

```bash
# Doxygen File will be generated in docs/html/index.html
make docs       # generates docs/ via Doxygen
```

## Architecture

```
| - main.c          — entry point
| - src          
| | - turtsh.h        
| | - turtsh.c        
| | - builtins.h        
| | - builtins.c        
| | - Parser        
| | | - parser.c        
| | | - parser.h        
```



