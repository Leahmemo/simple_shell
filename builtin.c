#include "shell.h"

/**
 * my_exit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info->argv[0] != "exit"
 */
int my_exit(info_t *info)
{
	int exit_check;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exit_check = str_to_int(info->argv[1]);
		if (exit_check == -1)
	{
		info->status = 2;
		print_error(info, "Illegal number: ");
		e_puts(info->argv[1]);
		e_putchar('\n');
		return (1);
	}
	info->err_num = str_to_int(info->argv[1]);
	return (-2);
	}
		info->err_num = -1;
		return (-2);
	}

/**
 * my_cd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int my_cd(info_t *info)
{
	char *current_dir, *new_dir, buffer[1024];
	int chdir_ret;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		e_puts("TODO: >>getcwd failure emsg here<<\n");
		if (!info->argv[1])
	{
	new_dir = _getenv(info, "HOME=");
	if (!new_dir)
		chdir((new_dir = _getenv(info, "PWD=")) ? new_dir : "/");
	else
		chdir_ret = chdir(new_dir);
	}
		else if (_strcmp(info->argv[1], "-") == 0)
	{
	if (!_getenv(info, "OLDPWD="))
	{
		e_puts(current_dir);
		e_putchar('\n');
		return (1);
	}
	e_puts(_getenv(info, "OLDPWD=")), e_putchar('\n');
	chdir((new_dir = _getenv(info, "OLDPWD=")) ? new_dir : "/");
	}
		else
        chdir_ret = chdir(info->argv[1]);
    if (chdir_ret == -1)
    {
        print_error(info, "can't cd to ");
        e_puts(info->argv[1]);
        e_putchar('\n');
    }
    else
    {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}

/**
 * my_help - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int my_help(info_t *info)
{
    char **arg_array;

    arg_array = info->argv;
    e_puts("help call works. Function not yet implemented \n");
    if (0)
        e_puts(*arg_array); /* temp att_unused workaround */
    return (0);
}
