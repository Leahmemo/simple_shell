#include "shell.h"

/**
 * _strcpy - copies a string
 * @destination: pointer to the destination buffer
 * @source: pointer to the source string
 *
 * Return: pointer to destination
 */
char *_strcpy(char *destination, char *source)
{
	int index = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[index])
	{
		destination[index] = source[index];
		index++;
	}
	destination[index] = '\0'; /* Null-terminate the destination string */
	return (destination);
}

/**
 * _strdup - duplicates a string
 * @input_str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *input_str)
{
	int length = 0;
	char *result;

	if (input_str == NULL)
		return (NULL);
	while (*input_str++)
		length++;
	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	for (length++; length--;)
		result[length] = *--input_str;
	return (result);
}

/**
 * _puts - prints an input string
 * @string_to_print: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *string_to_print)
{
	int index = 0;

	if (!string_to_print)
		return;
	while (string_to_print[index] != '\0')
	{
		_putchar(string_to_print[index]);
		index++;
	}
}

/**
 * _putchar - writes the character to stdout
 * @character: The character to print
 *
 * Return:
 *   - On success, it returns 1.
 *   - On error, it returns -1, and errno is set appropriately.
 */
int _putchar(char character)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (character == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (character != BUF_FLUSH)
		buffer[i++] = character;
	return (1);
}
