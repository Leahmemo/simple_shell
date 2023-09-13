#include "shell.h"

/**
 * new_eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void new_eputs(char *str)
{
	int new_i = 0;

	if (!str)
		return;
	while (str[new_i] != '\0')
	{
		new_eputchar(str[i]);
		new_i++;
	}
}

/**
 * new_eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int new_eputchar(char c)
{
	static int new_i;
	static char new_buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || new_i >= WRITE_BUF_SIZE)
	{
		write(2, buf, new_i);
		new_i = 0;
	}
	if (c != BUF_FLUSH)
		buf[new_i++] = c;
	return (1);
}

/**
 * new_putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int new_putfd(char c, int fd)
{
	static int new_i;
	static char new_buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || new_i >= WRITE_BUF_SIZE)
	{
		write(fd, new_buf, new_i);
		new_i = 0;
	}
	if (c != BUF_FLUSH)
		new_buf[new_i++] = c;
	return (1);
}

/**
 * new_putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int new_putsfd(char *str, int fd)
{
	int new_i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		new_i += new_putfd(*str++, fd);
	}
	return (new_i);
}

