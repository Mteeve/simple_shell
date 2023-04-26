#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUF_SIZE 1024

static char **parse_args(char *buffer);
static void execute_command(char **args);


/**
* main - Entry point for the program
*
* Return: 0 on success
*/
int main(void)
{
char *buffer = NULL;
size_t bufsize = 0;
ssize_t n_read = 0;

while (1)
{
printf("$ ");
n_read = getline(&buffer, &bufsize, stdin);
if (n_read == -1)
{
perror("getline");
exit(EXIT_FAILURE);
}
buffer[n_read - 1] = '\0';

if (strcmp(buffer, "exit") == 0)
{
free(buffer);
exit(EXIT_SUCCESS);
}

char **args = parse_args(buffer);
execute_command(args);

free(args);
}

return (0);
}


/**
* Parses the command line arguments from the buffer.
*
* @param buffer The command line buffer.
*
* @return The arguments parsed from the buffer.
*/
static char **parse_args(char *buffer)
{
char **args = malloc(sizeof(char *) * BUF_SIZE);
if (!args)
{
perror("malloc");
exit(EXIT_FAILURE);
}

int i, j;
for (i = 0, j = 0; buffer[i]; i++)
{
if (buffer[i] == ' ')
{
buffer[i] = '\0';
args[j] = &buffer[i + 1];
j++;
}
}
args[j] = NULL;

return (args);
}


/**
* Executes the command with the given arguments.
*
* @param args The command line arguments.
*/
static void execute_command(char **args)
{
pid_t child_pid = fork();
if (child_pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}

if (child_pid == 0)
{
if (execvp(args[0], args) == -1)
{
perror("execvp");
exit(EXIT_FAILURE);
}
}
else
{
wait(NULL);
}
}
