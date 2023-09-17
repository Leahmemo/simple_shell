/**
 * custom_get_history_file - gets the custom history file
 * @info: parameter structure
 *
 * Return: allocated string containing the custom history file
 */

char *custom_get_history_file(info_t *info)
{
	char *dir, *history_file;

	dir = _custom_getenv(info, "HOME=");
	if (!dir)
		return (NULL);

	history_file = malloc(sizeof(char) * (_custom_strlen(dir) + _custom_strlen(CUSTOM_HIST_FILE) + 2));
	if (!history_file)
		return (NULL);

	history_file[0] = 0;
	_custom_strcpy(history_file, dir);
	_custom_strcat(history_file, "/");
	_custom_strcat(history_file, CUSTOM_HIST_FILE);

	return (history_file);
}

/**
 * custom_write_history - creates a file, or appends to an existing file
 * @info: the parameter structure
 *
 * Return: 1 on success, else -1
 */
int custom_write_history(info_t *info)
{
	ssize_t fd;
	char *filename = custom_get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fd == -1)
		return (-1);

	for (node = info->custom_history; node; node = node->next)
	{
		_custom_putsfd(node->str, fd);
		_custom_putfd('\n', fd);
	}

	_custom_putfd(CUSTOM_BUF_FLUSH, fd);
	close(fd);

	return (1);
}

/**
 * custom_read_history - reads custom history from file
 * @info: the parameter structure
 *
 * Return: custom histcount on success, 0 otherwise
 */
int custom_read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = custom_get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);

	if (fd == -1)
		return (0);

	if (!fstat(fd, &st))
	fsize = st.st_size;

	if (fsize < 2)
		return (0);

	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);

	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;

	if (rdlen <= 0)
		return (free(buf), 0);

	close(fd);

	for (i = 0; i < fsize; i++)
	{
	if (buf[i] == '\n')
	}
		buf[i] = 0;
		custom_build_history_list(info, buf + last, linecount++);
		last = i + 1;
		}
	}

	if (last != i)
	custom_build_history_list(info, buf + last, linecount++);

	free(buf);
	info->custom_histcount = linecount;

	while (info->custom_histcount-- >= CUSTOM_HIST_MAX)
		custom_delete_node_at_index(&(info->custom_history), 0);

		custom_renumber_history(info);

	return (info->custom_histcount);
}

/**
 * custom_build_history_list - adds entry to a custom history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int custom_build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->custom_history)
		node = info->custom_history;

	custom_add_node_end(&node, buf, linecount);

	if (!info->custom_history)
	info->custom_history = node;

	return (0);
}

/**
 * custom_renumber_history - renumbers the custom history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int custom_renumber_history(info_t *info)
{
	list_t *node = info->custom_history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return (info->custom_histcount = i);
}
