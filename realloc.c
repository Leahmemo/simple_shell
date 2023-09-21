#include <stdlib.h>
#include 'shell.h'
/**
 * custom_memset - fills memory with a custom constant byte
 * @custom_ptr: pointer to the custom memory area
 * @custom_byte: the custom byte to fill *custom_ptr with
 * @custom_size: the custom amount of bytes to be filled
 * Return: (custom_ptr) a pointer to the custom memory area custom_ptr
 */
char *custom_memset(char *custom_ptr, char custom_byte, unsigned int custom_size)
{
	unsigned int i;

	for (i = 0; i < custom_size; i++)
		custom_ptr[i] = custom_byte;

	return (custom_ptr);
}

/**
 * custom_free_strings - frees an array of strings
 * @custom_strings: array of strings to be freed
 */
void custom_free_strings(char **custom_strings)
{
	char **custom_ptr = custom_strings;

	if (!custom_strings)
		return;

	while (*custom_strings)
		free(*custom_strings++);

	free(custom_ptr);
}

/**
 * custom_reallocate - custom reallocation of memory block
 * @custom_ptr: pointer to the previous custom memory block
 * @custom_old_size: byte size of the previous custom block
 * @custom_new_size: byte size of the new custom block
 *
 * Return: pointer to the updated custom memory block
 */
void *custom_reallocate(void *custom_ptr, unsigned int custom_old_size, unsigned int custom_new_size)
{
	char *custom_new_ptr;

	if (!custom_ptr)
		return (malloc(custom_new_size));

	if (!custom_new_size)
		return (free(custom_ptr), NULL);

	if (custom_new_size == custom_old_size)
		return (custom_ptr);

	custom_new_ptr = malloc(custom_new_size);

	if (!custom_new_ptr)
		return (NULL);

	custom_old_size = custom_old_size < custom_new_size ? custom_old_size : custom_new_size;

	while (custom_old_size--)
		custom_new_ptr[custom_old_size] = ((char *)custom_ptr)[custom_old_size];

	free(custom_ptr);
	return (custom_new_ptr);
}
