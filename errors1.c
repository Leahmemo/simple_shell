#include "shell.h"

/**
 * _customerratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _customerratoi(char *s)
{
	int index = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;  /* TODO: why does this make main return 255? */
	for (index = 0;  str[index] != '\0'; index++)
	{
		if (str[index] >= '0' && str[index] <= '9')
		{
			result *= 10;
			result += (str[index] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_customError - prints an error message
 * @info: the parameter & return info struct
 * @errorstring: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_customError(info_t *info, char *errorstring)
{
	_customPuts(info->fname);
	_customePuts(": ");
	print_customDecimal(info->line_count, STDERR_FILENO);
	_customPuts(": ");
	_customputs(info->argv[0]);
	_customputs(": ");
	_customputs(estr);
}

/**
 * print_customDecimal - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_customDecimal(int input, int fd)
{
	int (*custompchar)(char) = _custompchar;
	int i, count = 0;
	unsigned int _absolute, current;

	if (fd == STDERR_FILENO)
		custompchar = _custompchar;
	if (input < 0)
	{
		absolute_ = -input;
		custompchar('-');
		count++;
	}
	else
		absolute = input;
	current = absolute;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute / i)
		{
			custompchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	custompchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_customNumber - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_customNumber(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_customComments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_customComments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

