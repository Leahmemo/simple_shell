#include "shell.h"

/**
 * input_buff - buffers chained commands
 * @info: parameter struct
 * @buff: address of the buffer
 * @len: address of length var
 *
 * Return: bytes read
 */
ssize_t input_buff(info_t *info, char **buff, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, customSigintHandler);
#if USE_GETLINE
		r = getline(buff, &len_p, stdin);
#else
		r = _getline(info, buff, &len_p);
#endif
		if (r > 0)
		{
			if ((*buff)[r - 1] == '\n')
			{
				(*buff)[r - 1] = '\0';
				r--;
			}
			info->linecnt_flg = 1;
			remove_customComments(*buff);
			custom_build_history_list(info, *buff, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buff;
			}
		}
	}
	return (r);
}

/**
 * get_the_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_the_input(info_t *info)
{
	static char *buff;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buff_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buff(info, &buff, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buff + i;

		check_chain(info, buff, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buff, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buff_p = p;
		return (_strlen(p));
	}

	*buff_p = buff;
	return (r);
}

/**
 * read_buff - reads a buffer
 * @info: parameter struct
 * @buff: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buff(info_t *info, char *buff, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buff, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buff(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strcat(new_p, buf + i, k - i);
	else
		_strcpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * customSigintHandler - HANDLES  the SIGNINT signal ctrl C
 * @signal_num: the signal number
 *
 * Return: void
 */
void customSigintHandler(__attribute__((unused))int signal_num)
{
	_puts("\n");
	_puts("$ CustomShell > ");
	_putchar(BUF_FLUSH);
}

