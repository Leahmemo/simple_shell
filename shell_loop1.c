#include "shell.h"

/**
* main_shell_loop - main shell loop
* @info: the parameter & return info struct
* @argv: the argument vector from main()
*
* Return: 0 on success, 1 on error, or error code
*/
int main_shell_loop(info_t *info, char **argv)
{
ssize_t input_result = 0;
int builtin_result = 0;

while (input_result != -1 && builtin_result != -2)
{
clearenv(info);
if (interactive(info))
_puts("$ ");
_putchar(BUF_FLUSH);
input_result = get_the_input(info);
if (input_result != -1)
{
set_info(info, argv);
builtin_result = find_builtin(info);
if (builtin_result == -1)
find_command(info);
}
else if (interactive(info))
_putchar('\n');
free_info(info, 0);
}
write_history(info);
free_info(info, 1);
if (!interactive(info) && info->status)
exit(info->status);
if (builtin_result == -2)
{
if (info->err_nm == -1)
exit(info->status);
exit(info->err_nm);
}
return (builtin_result);
}

/**
* find_builtin_command - finds a builtin command
* @info: the parameter & return info struct
*
* Return: -1 if builtin not found,
* 0 if builtin executed successfully,
* 1 if builtin found but not successful,
* 2 if builtin signals exit()
*/
int find_builtin_command(info_t *info)
{
int i, builtin_result = -1;
builtin_table builtintbl[] = {
{"exit", my_exit},
{"env", myenv},
{"help", my_help},
{"history", _myhistory},
{"setenv", mysetenv},
{"unsetenv", myunsetenv},
{"cd", _mycd},
{"alias", _myalias},
{NULL, NULL}
};

for (i = 0; builtintbl[i].typ; i++)
if (_strcmp(info->argv[0], builtintbl[i].typ) == 0)
{
info->line_cnt++;
builtin_result = builtintbl[i].func(info);
break;
}
return (builtin_result);
}

/**
* find_executable_command - finds a command in PATH
* @info: the parameter & return info struct
*
* Return: void
*/
void find_executable_command(info_t *info)
{
char *path = NULL;
int i, k;

info->path = info->argv[0];
if (info->linecnt_flg == 1)
{
info->line_cnt++;
info->linecnt_flg = 0;
}
for (i = 0, k = 0; info->arg[i]; i++)
if (!is_delim(info->arg[i], " \t\n"))
k++;
if (!k)
return;

char *path = my_getenv("PATH");
if (path)
{
info->path = path;
fork_executable_command(info);
}
else
{
if ((interactive(info) || my_getenv(info, "PATH=")
|| info->argv[0][0] == '/') && is_command(info, info->argv[0]))
fork_executable_command(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
print_error(info, "not found\n");
}
}
}

/**
* fork_executable_command - forks an exec thread to run cmd
* @info: the parameter & return info struct
*
* Return: void
*/
void fork_executable_command(info_t *info)
{
pid_t child_pid;

child_pid = fork();
if (child_pid == -1)
{
	perror("Error:");
	return;
}
if (child_pid == 0)
{
if (execve(info->path, info->argv, my_getenv(info)) == -1)
{
free_info(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}

}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
print_error(info, "Permission denied\n");
}
}
}
