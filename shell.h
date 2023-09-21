#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */

typedef struct liststrg
{
	int num;
	char *str;
	struct liststr *nxt;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_cnt: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_chngd: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buff: address of pointer to cmd_buf, on if chaining
 * @cmd_buff_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_cnt;
	int err_nm;
	int linecnt_flg;
	char *filename;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_chgd;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer*/
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}
/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */

typedef struct builtin
{
	char *typ;
	int (*func)(info_t *);
} builtin_table;


/* shell_loop1.c */
int main_shell_loop(info_t *info, char **argv);
int find_builtin_command(info_t *info);
void find_executable_command(info_t *info);
void fork_executable_command(info_t *info);

/* parser1.c */
int is_executable(info_t *info, char *file_path);
char *extract_substring(char *source, int start, int end);
char *find_command_in_path(info_t *info, char *path_string, char *command);


/* errors.c */
void new_eputs(char *str);
int new_eputchar(char c);
int new_putfd(char c, int fd);
int new_putsfd(char *str, int fd);

/* string1.c */
int _strlen(char *str);
int _strcmp(char *str1, char *str2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);

/* string2.c */
char *_strcpy(char *, char *);
char *_strdup(const char *input_str);
void _puts(char *string_to_print);
int _putchar(char character);

/* exiting.c */
char *_custom_strncpy(char *, char *, int);
char *_custom_strncat(char *, char *, int);
char *_custom_strchr(char *, char);

/* token1r.c */
char **str_to_words(char *, char *);
char **str_to_words2(char *, char);

/* realloc.c */
char *custom_memset(char *, char, unsigned int);
void custom_free_strings(char **);
void *custom_reallocate(void *, unsigned int, unsigned int);

/* mem.c */
int my_free(void **);

/* _atoi.c */
int is_shell_interactive(info_t *);
int is_character_delimiter(char, char *);
int is_alpha_character(int);
int custom_atoi(char *);

/* errors1.c */
int _customerratoi(char *);
void print_customError(info_t *, char *);
int print_customDecimal(int, int);
char *convert_customNumber(long int, int, int);
void remove_customComments(char *);

/* builtin.c */
int my_exit(info_t *);
int my_cd(info_t *);
int my_help(info_t *);


/*getlinefn.c */
ssize_t get_the_input(info_t *);
int _getline(info_t *, char **, size_t *);
void customSigintHandler(int);

/* getinfo.c */
void custom_clear_info(info_t *);
void custom_set_info(info_t *, char **);
void custom_free_info(info_t *, int);

/* environ.c */
char *getenv(info_t *, const char *);
int myenv(info_t *);
int mysetenv(info_t *);
int myunsetenv(info_t *);
int populate_env_list(info_t *);

/* getenv.c */
char **custom_get_environ(info_t *);
int custom_unsetenv(info_t *, char *);
int custom_setenv(info_t *, char *, char *);

/* gethistory.c */
char *custom_get_history_file(info_t *info);
int custom_write_history(info_t *info);
int custom_read_history(info_t *info);
int custom_build_history_list(info_t *info, char *buf, int linecount);
int custom_renumber_history(info_t *info);

/* getlists.c */
list_t *custom_add_node(list_t **, const char *, int);
list_t *custom_add_node_end(list_t **, const char *, int);
size_t custom_print_list_str(const list_t *);
int custom_delete_node_at_index(list_t **, unsigned int);
void custom_free_list(list_t **);

/* verse.c */
int is_custom_hain(info_t *, char *, size_t *);
void check_custom_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_custom_alias(info_t *);
int replace_custom_vars(info_t *);
int replace_custom_string(char **, char *);

#endif

