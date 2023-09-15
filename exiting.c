/**
 **_custom_strncpy - custom string copy function
 *@dest: destination string to be copied to
 *@src: source string
 *@n: maximum number of characters to copy
 *Return: pointer to the copied string
 */
char *_custom_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *result = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (result);
}

/**
 **_custom_strncat - custom string concatenation function
 *@dest: first string
 *@src: second string
 *@n: maximum number of bytes to concatenate
 *Return: pointer to the concatenated string
 */
char *_custom_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *result = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (result);
}

/**
 **_custom_strchr - custom character search in a string
 *@s: string to be searched
 *@c: character to find
 *Return: pointer to the found character or NULL if not found
 */
char *_custom_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

