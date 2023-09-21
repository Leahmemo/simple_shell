#include "shell.h"

/**
 * custom_add_node - adds a custom node to the beginning of the list
 * @custom_head: address of pointer to custom head node
 * @custom_str: custom str field of the node
 * @custom_num: custom node index used for history
 *
 * Return: pointer to the new custom node
 */
list_t *custom_add_node(list_t **custom_head, const char *custom_str, int custom_num)
{
	list_t *new_custom_head;

	if (!custom_head)
		return (NULL);

	new_custom_head = malloc(sizeof(list_t));
	if (!new_custom_head)
		return (NULL);

	memset((void *)new_custom_head, 0, sizeof(list_t));
	new_custom_head->num = custom_num;

	if (custom_str)
	{
		new_custom_head->custom_str = _strdup(custom_str);
		if (!new_custom_head->custom_str)
	{
		free(new_custom_head);
		return (NULL);
	}
	}

	new_custom_head->nxt = *custom_head;
	*custom_head = new_custom_head;

	return (new_custom_head);
}

/**
 * custom_add_node_end - adds a custom node to the end of the list
 * @custom_head: address of pointer to custom head node
 * @custom_str: custom str field of the node
 * @custom_num: custom node index used for history
 *
 * Return: pointer to the new custom node
 */
list_t *custom_add_node_end(list_t **custom_head, const char *custom_str, int custom_num)
{
	list_t *new_custom_node, *custom_node;

	if (!custom_head)
		return (NULL);

	custom_node = *custom_head;
	new_custom_node = malloc(sizeof(list_t));

	if (!new_custom_node)
		return (NULL);

	memset((void *)new_custom_node, 0, sizeof(list_t));
	new_custom_node->num = custom_num;

	if (custom_str)
	{
		new_custom_node->custom_str = _strdup(custom_str);
		if (!new_custom_node->custom_str)
	{
		free(new_custom_node);
		return (NULL);

	}
	}

	if (custom_node)
	{
		while (custom_node->nxt)
		custom_node = custom_node->nxt;
		custom_node->nxt = new_custom_node;
	}
	else
		*custom_head = new_custom_node;

	return (new_custom_node);
}

/**
 * custom_print_list_str - prints only the custom_str element of a custom list_t linked list
 * @custom_h: pointer to the first custom node
 *
 * Return: size of the custom list
 */
size_t custom_print_list_str(const list_t *custom_h)
{
	size_t i = 0;

	while (custom_h)
	{
		_custom_alias(custom_h->custom_str ? custom_h->custom_str : "(nil)");
		_custom_alias("\n");
		custom_h = custom_h->nxt;
	i++;
	}

	return (i);
}

/**
 * custom_delete_node_at_index - deletes a custom node at the given index
 * @custom_head: address of pointer to the first custom node
 * @custom_index: index of the custom node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int custom_delete_node_at_index(list_t **custom_head, unsigned int custom_index)
{
	list_t *custom_node, *prev_custom_node;
	unsigned int i = 0;

	if (!custom_head || !*custom_head)
		return (0);

	if (!custom_index)
	{
		custom_node = *custom_head;
		*custom_head = (*custom_head)->nxt;
		free(custom_node->custom_str);
		free(custom_node);
		return (1);
	}

	custom_node = *custom_head;

	while (custom_node)
	{
		if (i == custom_index)
	{
		prev_custom_node->nxt = custom_node->nxt;
		free(custom_node->custom_str);
		free(custom_node);
		return (1);
	}

		i++;
		prev_custom_node = custom_node;
		custom_node = custom_node->nxt;
	}

	return (0);
}

/**
 * custom_free_list - frees all custom nodes of a custom list
 * @custom_head_ptr: address of pointer to custom head node
 *
 * Return: void
 */
void custom_free_list(list_t **custom_head_ptr)
{
	list_t *custom_node, *next_custom_node, *custom_head;

	if (!custom_head_ptr || !*custom_head_ptr)
		return;

	custom_head = *custom_head_ptr;
	custom_node = custom_head;

	while (custom_node)
	{
		next_custom_node = custom_node->nxt;
		free(custom_node->custom_str);
		free(custom_node);
		custom_node = next_custom_node;
	}

	*custom_head_ptr = NULL;
}
