/**
 * check_interactivity - determines if the shell is in interactive mode
 * @info: pointer to info structure
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int check_interactivity(info_t *info)
{
	return (is_terminal(STDIN_FILENO) && info->read_fd <= 2);
}

/**
 * is_separator - checks if a character is a separator
 * @c: the character to check
 * @separators: a string of separators
 * Return: 1 if it's a separator, 0 otherwise
 */
int is_separator(char c, char *separators)
{
	while (*separators)
	{
		if (*separators++ == c)
		return (1);
	}
	return (0);
}

/**
 * is_alphabetic - checks if a character is alphabetic
 * @c: the character to check
 * Return: 1 if it's alphabetic, 0 otherwise
 */
int is_alphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

/**
 * custom_atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, the converted number otherwise
 */
int custom_atoi(char *s)
{
	int i, sign = 1, flag = 0, result;
	unsigned int value = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
	if (s[i] == '-')
		sign *= -1;

	if (s[i] >= '0' && s[i] <= '9')
	{
		flag = 1;
		value *= 10;
		value += (s[i] - '0');
	}
	else if (flag == 1)
		flag = 2;
	}

	result = sign * value;
	return (result);
}

