#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


#define PROMPT "#cisfun$ "
#define BUFFER_SIZE 1024
#define MAX_ARGS 64

void parse_input(char *buffer, char *args[]);
/*
* parse_input - Parses the input command into separate arguments
*
* @buffer: the input command string
* @args: an array of strings to store the parsed arguments
*/

void execute_command(char *args[]);
/*
* execute_command - Executes the command in a child process
*
* @args: an array of strings containing the command and its arguments
*/

/**
* main - Entry point for the program
*
* Return: 0 on success
*/
int main(void)
{
char buffer[BUFFER_SIZE];
char *args[MAX_ARGS];

while (1)
{
printf("%s", PROMPT);

if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
{
printf("\n");
break;
}
buffer[strlen(buffer) - 1] = '\0';

parse_input(buffer, args);
execute_command(args);
}

return (0);
}

void parse_input(char *buffer, char *args[])
{
char *token;
int i = 0;

token = strtok(buffer, " ");

while (token != NULL && i < MAX_ARGS - 1)
{
args[i] = token;
token = strtok(NULL, " ");
i++;
}

args[i] = NULL;
}

void execute_command(char *args[])
{
pid_t pid;
int status;

pid = fork();
if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}

if (pid == 0)
{
if (execvp(args[0], args) == -1)
{
perror("shell");
exit(EXIT_FAILURE);
}
}
else
{
wait(&status);
}
}
