#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "shell.h"

/**
* hsh - main loop for interactive mode
*/
void hsh(void)
{
info_t info = INFO_INIT;
populate_env_list(&info);

while (1)
{
char *line = get_input(&info);
if (!line)
break;

execute_line(&info, line);
free(line);
}

free_info(&info);
exit(EXIT_SUCCESS);
}

/**
* get_input - read input line from stdin
* @info: info_t struct containing program information
*
* Return: input line or NULL on failure or EOF
*/
char *get_input(info_t *info)
{
char *line = NULL;
size_t len = 0;

if (isatty(STDIN_FILENO))
_puts("$ ");

if (getline(&line, &len, stdin) == -1)
return (NULL);

remove_comments(line);
replace_vars(info, &line);

return (line);
}

/**
* execute_line - execute commands from input line
* @info: info_t struct containing program information
* @line: input line to execute
*/
void execute_line(info_t *info, char *line)
{
char **args = tokenize(line);
if (!args || !args[0])
goto exit_func;

if (is_builtin(args[0]))
execute_builtin(info, args);
else
execute_external(info, args);

exit_func:
free_tokens(args);
}

/**
* execute_external - execute external command
* @info: info_t struct containing program information
* @args: arguments for command
*/
void execute_external(info_t *info, char **args)
{
pid_t pid;
int status;

pid = fork();
if (pid == -1)
{
perror("fork");
return;
}
else if (pid == 0)
{
/* child process */
if (execve(args[0], args, info->envp) == -1)
{
perror("execve");
exit(EXIT_FAILURE);
}
}
else
{
/* parent process */
do {
waitpid(pid, &status, WUNTRACED);
} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
}

/**
* execute_builtin - execute builtin command
* @info: info_t struct containing program information
* @args: arguments for command
*/
void execute_builtin(info_t *info, char **args)
{
int status;

if (_strcmp(args[0], "exit") == 0)
{
if (args[1])
status = _atoi(args[1]);
free_info(info);
exit(status);
}
else if (_strcmp(args[0], "env") == 0)
{
print_env(info->envp);
}
else if (_strcmp(args[0], "setenv") == 0)
{
if (args[1] && args[2])
set_env(&info->envp, args[1], args[2]);
}
else if (_strcmp(args[0], "unsetenv") == 0)
{
if (args[1])
unset_env(&info->envp, args[1]);
}
}

/**
* is_builtin - check if command is a builtin
* @cmd: command to check
*
* Return: 1 if builtin, 0 otherwise
*/
int is_builtin(char *cmd)
{
return (_strcmp(cmd, "exit") == 0 ||
_strcmp(cmd, "env") == 0 ||
_strcmp(cmd, "setenv") == 0 ||
_strcmp(cmd, "unsetenv") == 0);
}
