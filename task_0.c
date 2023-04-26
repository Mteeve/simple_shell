#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


#define BUF_SIZE 1024


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
char *args[100];
int status = 0;
int i = 0, j = 0;
pid_t child_pid;


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


if (strcmp(buffer, "exit") == 0)
{
free(buffer);
exit(EXIT_SUCCESS);
}


child_pid = fork();
if (child_pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}


if (child_pid == 0)
{
if (execve(args[0], args, NULL) == -1)
{
perror("./hsh");
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

