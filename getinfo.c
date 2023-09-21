#include "shell.h"

/**
 * custom_clear_info - initializes info_t struct
 * @info: struct address
 */
void custom_clear_info(info_t *info)
{
	info->custom_arg = NULL;
	info->custom_argv = NULL;
	info->custom_path = NULL;
	info->custom_argc = 0;
}

/**
 * custom_set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void custom_set_info(info_t *info, char **av)
{
	int i = 0;

	info->filename = av[0];
	if (info->custom_arg)
	{
		info->custom_argv = strtok(info->custom_arg, " \t");
		if (!info->custom_argv)
		{
			info->custom_argv = malloc(sizeof(char *) * 2);
			if (info->custom_argv)
			{
				info->custom_argv[0] = _strdup(info->custom_arg);
				info->custom_argv[1] = NULL;
			}
		}
		for (i = 0; info->custom_argv && info->custom_argv[i]; i++)
			;
		info->custom_argc = i;

		custom_replace_alias(info);
		custom_replace_vars(info);
	}
}

/**
 * custom_free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void custom_free_info(info_t *info, int all)
{
	free(info->custom_argv);
	info->custom_argv = NULL;
	info->custom_path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->custom_arg);
		if (info->custom_env)
			free_list(&(info->custom_env));
		if (info->custom_history)
			free_list(&(info->custom_history));
		if (info->custom_alias)
			free_list(&(info->custom_alias));
		free(info->custom_environ);
			info->custom_environ = NULL;
		free((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

