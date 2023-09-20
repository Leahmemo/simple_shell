#include "shell.h"

/**
 * **str_to_words - splits a string into words. Repeat delimiters are ignored
 * @input_str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **str_to_words(char *input_str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **words_array;

	if (input_str == NULL || input_str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; input_str[i] != '\0'; i++)
		if (!is_delim(str[i], d) &&
(is_delim(input_str[i + 1], d) || !input_str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && input_str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!words_array[j])
		{
			for (k = 0; k < j; k++)
				free(words_array[k]);
			free(words_array);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			words_array[j][m] = input_str[i++];
		words_array[j][m] = 0;
	}
	words_array[j] = NULL;
	return (words_array);
}

/**
 * **str_to_words2 - splits a string into words
 * @input_str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **str_to_words2(char *input_str, char d)
{
	int i, j, k, m, numwords = 0;
	char **words_array;

	if (input_str == NULL || input_str[0] == 0)
		return (NULL);
	for (i = 0; input_str[i] != '\0'; i++)
		if ((input_str[i] != d && input_str[i + 1] == d) ||
				    (input_str[i] != d && !input_str[i + 1]) || input_str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	words_array = malloc((1 + numwords) * sizeof(char *));
	if (!words_array)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (input_str[i] == d && input_str[i] != d)
			i++;
		k = 0;
		while (input_str[i + k] != d && input_str[i + k] && input_str[i + k] != d)
			k++;
		words_array[j] = malloc((k + 1) * sizeof(char));
		if (!words_array[j])
		{
			for (k = 0; k < j; k++)
				free(words_array[k]);
			free(words_array);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			words_array[j][m] = input_str[i++];
		words_array[j][m] = 0;
	}
	words_array[j] = NULL;
	return (words_array);
}

