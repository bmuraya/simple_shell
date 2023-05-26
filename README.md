# C - Simple Shell

Group project to be done in teams of 2 people 

It aims to learning  the Unix shell and a simple shell is to gain an understanding of how to interact with a computer's operating system using command-line interfaces **UNIX system**.

## Builtins
Our shell has support for the following built-in commands:

| File             | Definition                                                                                |
| ------------------- | ----------------------------------------------------------------------------------------- |
| Main.c            |  Entry Point of the shell program.                                          |
| shell.header                | prototype header file.                                                                    |
| Memory.c  | Memory allocation  checking of memory block |
| alias[name[='value]]| Reads aliases name                                                                        |
| unsetenv [var]      | Remove an environment variable.                                                           |
| cd [dir]            | Change the directory.                                                                     |
| help [built-in]     | Read documentation for a built-in.                                                        |
## insert flowchat here 

## Tasks
* Write a UNIX command line interpreter.
* Handle command lines with arguments
* Handle the 'PATH' 'fork' must not be called if the command doesn’t exist
* Implement the exit built-in, that 'exits' the 'shell' (You don’t have to handle any argument to the built-in exit)
* Implement the 'env' built-in, that prints the current environment
* Write your own 'getline' function
   * Use a buffer to read many chars at once and call the least possible the 'read' system call
   * You will need to use 'static' variables
   * You are not allowed to use `getline`
* handle arguments for the built-in `exit`
   * Usage: `exit status` , where `status` is an integer used to exit the shell    
* Implement the `setenv` and `unsetenv` builtin commands

* `setenv`
    * Initialize a new environment variable, or modify an existing one
    * Command syntax: `setenv VARIABLE VALUE`
    * Should print something on stderr on failure
* `unsetenv`
    * Remove an environment variable
    * Command syntax: `unsetenv VARIABLE`
    * Should print something on stderr on failure
    
* Implement the builtin command `cd`:

   * Changes the current directory of the process.
   * Command syntax: `cd [DIRECTORY]`
   * If no argument is given to `cd` the command must be interpreted like `cd $HOME`
   * You have to handle the command `cd -`
   * You have to update the environment variable `PWD` when you change directory
        `man` `chdir`, `man` `getcwd`
* Handle the commands separator `;`
* Handle the `&&` and `||` shell logical operators
* Implement the `alias` builtin command
* Usage: `alias [name[='value'] ...]`
    * `alias`: Prints a list of all aliases, one per line, in the form `name='value'`
    * `alias name [name2 ...]`: Prints the aliases `name, name2`, etc 1 per line, in the form `name='value'`
    * `alias name='value' [...]`: Defines an alias for each `name` whose `value` is given. If `name` is already an alias, replaces its value with `value`
* Handle variables replacement
* Handle the $? variable
* Handle the $$ variable
* Handle comments `(#)`
* Usage: simple_shell [filename]
* Your shell can take a file as a command line argument
* The file contains all the commands that your shell should run before exiting
* The file should contain one command per line
* In this mode, the shell should not print a prompt and should not read from stdin




### Authors

* **Babu Muraya** - https://github.com/bmuraya

* **Abraham Ayamigah** - https://github.com/Ayamigah16

