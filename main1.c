#include "shell.h"

/**
 * main - entry point
 * @argc: arg count
 * @argv: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	info_t info[] = { INFO_INIT };
	int file_descriptor = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (file_descriptor)
			: "r" (file_descriptor));

	if (argc == 2)
	{
		file_descriptor = open(argv[1], O_RDONLY);
		if (file_descriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_puts(argv[0]);
				_puts(": 0: Can't open ");
				_puts(argv[1]);
				_putchar('\n');
				_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = file_descriptor;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, argv);
	return (EXIT_SUCCESS);
}

