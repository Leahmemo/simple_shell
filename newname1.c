#include "shell.h"

/**
 * list_length - determines length of linked list
 * @list: pointer to first node
 *
 * Return: size of list
 */
size_t list_length(const list_t *list)
{
	size_t size = 0;

	while (list)
	{
		list = list->next;
		size++;
	}
	return (size);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *current_node = head;
	size_t size = list_length(head);
	char **strings_array;
	char *string;

	if (!head || !size)
		return (NULL);
	strings_array = malloc(sizeof(char *) * (size + 1));
	if (!strings_array)
		return (NULL);
	for (size = 0; current_node; current_node = current_node->next, size++)
	{
		string = malloc(_strlen(current_node->str) + 1);
		if (!string)
		{
			for (size_t j = 0; j < size; j++)
				free(strings_array[j]);
			free(strings);
			return (NULL);
		}

		string = _strcpy(string, current_node->str);
		strings_array[size] = string;
	}
	strings_array[size] = NULL;
	return (strings_array);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @list: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *list)
{
	size_t size = 0;

	while (list)
	{
		_puts(convert_number(list->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(list->str ? list->str : "(nil)");
		_puts("\n");
		list = list->next;
		size++;
	}
	return (size);
}

/**
 * find_node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *find_node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}

