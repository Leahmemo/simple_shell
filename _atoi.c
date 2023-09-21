#include "shell.h"

/**
 * is_shell_interactive - returns true if shell is interactive mode
 * @shell_info: struct address
 *
 * Return: 1 if the shell is in interactive mode, 0 otherwise
 */
int is_shell_interactive(info_t *shell_info)
{
	return (isatty(STDIN_FILENO) && shell_info->readfd <= 2);
}

/**
 * is_character_delimiter - checks if character is a delimeter
 * @character: the char to check
 * @delimiter: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_character_delimiter(char character, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == character)
			return (1);
	return (0);
}

/**
 * is_alpha_character - checks if a character is alphabetic
 * @character: The character to input
 * Return: 1 if the character is alphabetic, 0 otherwise
 */

int is_alpha_character(int character)
{
	if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * custom_atoi - converts a string to an integer
 * @input_string: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int custom_atoi(char *input_string)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; input_strings[i] != '\0' && flag != 2; i++)
	{
		if (input_string[i] == '-')
			sign *= -1;

		if (input_string[i] >= '0' && input_string[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
