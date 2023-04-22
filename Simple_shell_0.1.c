#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define PROMPT "#cisfun$ "
#define BUFFER_SIZE 1024

/**
* main - Entry point for the program
*
* Return: 0 on success
*/

int main(void)
{
char buffer[BUFFER_SIZE];
char *args[2];
pid_t pid;
int status;

while (1)
{
printf("%s", PROMPT);
if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
{
printf("\n");
break;
}
buffer[strlen(buffer) - 1] = '\0';

args[0] = buffer;
args[1] = NULL;

pid = fork();
if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
if (pid == 0)
{
if (execve(args[0], args, NULL) == -1)
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
return (0);
}
