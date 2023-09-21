#include "shell.h"

/**
 * is_executable - determines if a file is an executable command
 * @info: the info struct
 * @file_path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_executable(info_t *info, char *file_path)
{
	struct stat file_stat;

	(void)info;
	if (!file_path || stat(file_path, &file_stat))
		return (0);

	if (S_ISREG(file_stat.st_mode))
	{
		return (1);
	}
	return (0);
}

/**
 * extract_substring - extracts characters from a string.
 * @source: the PATH string
 * @start: starting index
 * @end: ending index
 *
 * Return: pointer to new buffer
 */
char *extract_substring(char *source, int start, int end)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < end; i++)
		if (source[i] != ':')
			buffer[k++] = source[i];
	buffer[k] = 0;
	return (buffer);
}

/**
 * find_command_in_path - finds this cmd in the PATH string
 * @info: the info struct
 * @path_string: the PATH string
 * @command: the command to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_command_in_path(info_t *info, char *path_string, char *command)
{
	int i = 0, curentr_position = 0;
	char *path;

	if (!path_string)
		return (NULL);
	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (is_executable(info, command))
			return (command);
	}
	while (1)
	{
		if (!path_string[i] || path_string[i] == ':')
		{
			path = extract_substring(path_string, curentr_position, i);
			if (!*path)
				strcat(path, command);
			else
			{
				strcat(path, "/");
				strcat(path, command);
			}
			if (is_executable(info, path))
				return (path);
			if (!path_string[i])
				break;
			curentr_position = i;
		}
		i++;
	}
	return (NULL);
}

