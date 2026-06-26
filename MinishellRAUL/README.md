*This project has been created as part of the 42 curriculum by claherna, raulsanc.*

# Minishell

## Description

Minishell is a simple shell implementation written in C, inspired by Bash. It reads and executes user commands through an interactive prompt, handling features such as pipes, redirections, environment variable expansion, signal management, and built-in commands.

The goal of this project is to understand how a Unix shell works under the hood — from tokenizing and parsing user input to forking processes and managing file descriptors.

## Instructions

### Requirements

- A Unix-like operating system (Linux / macOS)
- `cc` compiler
- `make`
- `readline` library (`libreadline-dev` on Debian/Ubuntu)

### Compilation

```bash
make        # Compiles the project
make clean  # Removes object files
make fclean # Removes object files and the binary
make re     # Full recompile
```

### Execution

```bash
./minishell
```

Once running, the shell displays a prompt (`minishell$`) and waits for commands. It supports:

- **Builtins**: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- **Pipes**: `cmd1 | cmd2 | cmd3`
- **Redirections**: `<`, `>`, `>>`, `<<` (heredoc)
- **Environment variables**: `$VAR`, `$?`
- **Quotes**: single (`'`) and double (`"`) with proper expansion rules
- **Signals**: `Ctrl-C`, `Ctrl-D`, `Ctrl-\` behave like in Bash

## Resources

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [The Open Group — Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
- [Minishell subject (42)](subject/es.subject_minishell.pdf)
- `man bash`, `man readline`, `man 2 pipe`, `man 2 dup2`, `man 2 execve`, `man 2 fork`

### AI Usage

AI tools were used during this project as a support resource for:

- Understanding technical concepts, terminology, and usage of system calls and shell mechanisms
- Verifying expected behavior of commands and comparing outputs against Bash as a reference
