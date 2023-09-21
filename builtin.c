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
		_puts(info->argv[1]);
		_putchar('\n');
		return (1);
	}
	info->err_nm = str_to_int(info->argv[1]);
	return (-2);
	}
		info->err_nm = -1;
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
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
	new_dir = getenv(info, "HOME=");
	if (!new_dir)
		chdir((new_dir = getenv(info, "PWD=")) ? new_dir : "/");
	else
		chdir_ret = chdir(new_dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
	if (!getenv(info, "OLDPWD="))
	{
		_puts(current_dir);
		_putchar('\n');
		return (1);
	}
	_puts(getenv(info, "OLDPWD=")), _putchar('\n');
	chdir((new_dir = _getenv(info, "OLDPWD=")) ? new_dir : "/");
	}
		else
	chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_puts(info->argv[1]);
		_putchar('\n');
	}
	else
	{
		setenv(info, "OLDPWD", getenv(info, "PWD="));
		setenv(info, "PWD", getcwd(buffer, 1024));
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
		e_puts(*arg_array);
	return (0);
}
