# Unix Shells and Utilities

A collection of Unix-style command-line utilities and shell implementations written in C as part of my Linux System Programming practice.

The goal of these programs was to understand Linux system calls, process management, file descriptors, environment variables, directory operations, and command execution by implementing simplified versions of common Unix tools and shells.

## Unix Utilities

### mycp

A simplified implementation of the Unix `cp` command.

**Concepts practiced:**
- `open()`
- `read()`
- `write()`
- `close()`
- File descriptors
- File permissions

### mymv

A simplified implementation of the Unix `mv` command.

The program copies the source file to the destination and removes the original file using `unlink()`.

**Concepts practiced:**
- File I/O
- File descriptors
- `unlink()`
- System calls

### mypwd

A simplified implementation of the Unix `pwd` command using `getcwd()` to retrieve the current working directory.

### myecho

A simplified implementation of the Unix `echo` command that prints command-line arguments.

---

## Shell Implementations

### FemtoShell

A minimal shell implementation supporting basic built-in commands such as:

- `echo`
- `exit`

It also handles empty input and unsupported commands.

### PicoShell

Adds filesystem and directory navigation features.

**Supported functionality:**
- `echo`
- `pwd`
- `cd`
- `exit`

**Concepts practiced:**
- `getcwd()`
- `chdir()`
- Command parsing

### NanoShell

Adds shell-variable and environment-variable functionality.

**Features:**
- Local shell variables
- Variable reassignment
- `$variable` expansion
- `export`
- `printenv`
- `ls`
- `pwd`
- `cd`
- `echo`
- `exit`

This shell helped me understand the difference between shell-local variables and environment variables.

### MicroShell

Introduces process creation and execution of external programs.

**Concepts practiced:**
- `fork()`
- `execvp()`
- `wait()`
- File descriptors
- `dup2()`
- Standard output redirection
- Standard error redirection
- Parent and child processes

This was the main exercise for understanding how a Unix shell launches and manages programs.

---

## Linux System Programming Concepts Practiced

Through these exercises I worked with:

- Linux system calls
- Process creation and management
- Program execution
- File descriptors
- File I/O
- Directory management
- Environment variables
- Shell variables
- I/O redirection
- Parent/child process synchronization
