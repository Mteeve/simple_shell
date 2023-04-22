# simple_shell
Joint C - Simple Shell project by Doreen and Mteeve...

General Requirements in the project:
Allowed editors: vi, vim, emacs
All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
All your files should end with a new line
A README.md file, at the root of the folder of the project is mandatory
Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
Your shell should not have any memory leaks
No more than 5 functions per file
All your header files should be include guarded
Use system calls only when you need to (why?)
Write a README with the description of your project
You should have an AUTHORS file at the root of your repository, listing all individuals having contributed content to the repository. Format, see Docker


Task_0.c
This simple shell program reads input from the user and executes the command using execve. It continues to prompt the user for input until the user types "exit", then the program will exit.

Simple shell 0.1
This code implementation reads input from the user using fgets, parses the input into an array of strings, and then executes the command using execve. If an executable cannot be found, an error message is printed using perror.
To handle the "end of file" condition, the program checks if fgets returns NULL. If it does, the program exits.

Simple shell 0.2
This code uses strtok to parse the input into an array of strings, which can include arguments to the command. The array of strings is then passed to execvp, which can handle commands with arguments.

Simple shell 0.3
Code uses access to check if the command exists and is executable before forking. It also uses execvp to search for the command in the directories listed in the PATH environment variable.

Simple shell 0.4
Code checks if the user has entered the exit command and exits the shell if so.
To exit the shell, the user can simply type exit at the prompt. The strcmp function is used to compare the user input with the string "exit". If the strings are equal, the program breaks out of the loop and terminates.

Simple shell 1.0
Code checks if the user has entered the env command and prints the current environment if so.
To print the current environment, the __environ variable is used, which is a global variable that holds the current environment. The env command simply loops through the __environ array and prints each environment variable to the console.
