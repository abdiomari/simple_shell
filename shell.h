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

/* READ AND WRITE BUFFERS */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/*COMMAND CHAINING */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/*CONVERT NUMBER */
#define CONVERT_LOWERCASE		1
#define	CONVERT_UNSIGNED		2

/*1 FOR GETlINE()*/
#define USE_GETLINE	0
#define USE_STRTOK	0

#define HIST_FILE		".simple_shell_history"
#define HIST_MAX		4096

extern char **environ;


/**
 * struct liststr - this is a singly linked list
 * @num: defines the number field
 * @str: defines a string
 * @next: pointer that points to the next node
 */

typedef struct liststr
{
		int num;
		char *str;
		struct liststr *next;
} list_t;


/**
*@arg: A string generated from the "getline" function that contains the
arguments entered by the user.
*@argv": An array of strings generated from the "arg" string,
where each element represents an individual argument.
*@path": A string that contains the path of the current command being
executed.
*@argc": The number of arguments entered by the user.
*@line_count": An integer that keeps track of the number of errors
encountered during execution.
*@err_num": An integer that represents the error code for the "exit()"
function.
*@linecount_flag": A flag that, when enabled, causes the program t
o count the current line of input being executed.
*@fname": A string that contains the name of the shell program being executed.
*@env": A linked list that contains a local copy of the "environ" variable,
which stores the shell's environment variables.
*@environs": A custom-modified copy of the "environ" variable from the "env"
linked list. This copy is used to keep track of changes made to the environment
variables during program execution.
*@history": A node that is used to store the history of commands
executed in the shell.
*@alias": A node that is used to store aliases for commonly-used commands.
*@env_changed": A flag that is set to "true" if any changes are made to
the environment variables during program execution.
*@status": An integer that represents the return status of the last executed
command.
*@cmd_buf": A pointer to a pointer to a command buffer
. This is used when chaining commands together using operators
such as "||", "&&", and ";".
*@cmd_buf_type": An integer that represents the type of command
buffer being used. This can be "CMD_TYPE_OR", "CMD_TYPE_AND",
or "CMD_TYPE_NORMAL".
*@readfd": The file descriptor used to read input from the user.
*@histcount": An integer that keeps track of the number of lines
of input entered by the user.
*/

typedef struct passinfo
{
		char *arg;
		char **argv;
		char *path;
		int argc;
		unsigned int line_count;
		int err_num;
		int linecount_flag;
		char *fname;
		list_t *env;
		list_t *history;
		list_t *alias;
		char **environ;
		int env_changed;
		int status;

		char **cmd_buf;
		int cmd_buf_type;
		int readfd;
		int hiscount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
** struct builtin - contains a builtin string and related function
* @type: the builtin command flag
* @func: the function
*/

typedef struct builtin
{
		char *type;
		int (*func)(info_t *);
} builtin_table;

/* string to integer */
int is_interactive(info_t *);
int is_delimiter(char, char *);
int is_alpha(int);
int string_to_integer(char *);

/* builtin */
int exit_shell(shell_info_t *);
int change_directory(shell_info_t *);
int help_shell(shell_info_t *);

/* error repeat process*/
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* exits */
char *_sstrncpy(char *dest, const char *src, size_t n);
char *_sstrncat(char *dest, const char *src, size_t n);
char *_sstrchr(const char *s, int c);


/* getinfo */
void initialize_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* history */
char *get_hist_file(info_t *info);
int write_hist_file(info_t *info);
int read_hist_file(info_t *info);
int build_hist_file(info_t *info, char *buf, int linecount);
int renumber_hist_file(info_t *info);

/* toem_builtin1.c not done*/
int _myhistory(info_t *);
int _myalias(info_t *);

/* environs.c */
char print_env(info_t *info);
int *get_env_var(info_t *);
int set_env_var(info_t *);
int unset_env_var(info_t *);
int populate_env_list(info_t *);

/* errors.c */
void print_str_to_stderr(char *str);
int write_char_to_stderr(char);
int write_char_to_fd(char c, int fd);
int print_str_to_fd(char *str, int fd);

/* getenv.c */
char **get_env_strings(info_t *);
int remove_env_var(info_t *info, char *var_name);
int set_env_var(info_t *info, char *var_name, char *value);

/*getline.c */
ssize_t get_input(info_t *);
int get_input(info_t *info);
void read_buf(info_t *info, char *buf, size_t *i);

/* lists.c */
list_t *add_node_to_start(list_t **list_head, const char *str, int node_num);
list_t *add_node_to_end(list_t **list_head, const char *str, int node_num);
size_t print_list_strings(const list_t *list);
int delete_node_at_index(list_t **list_str, unsigned int index);
void free_linked_list(list_t **list_ptr);

/* lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);


/* vars.c */
int is_delimiter(info_t *info, char *buf, size_t *p);
void check_chain_status(info_t *info, char *buf, size_t *p, size_t i,
i size_t len);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int replace_string(char **old, char *new);


/* tokenizer.c */
char **split_string(char *str, char *delimiter);
char **split_string(char *input_string, char delimiter);

/* realloc.c */
char *_memset(char *, char, unsigned int);
void free_str_arr(char **str_arr);
void *_realloc(void *, unsigned int, unsigned int);

/* memory.c */
int free_and_nullify(void **ptr);

/* string.c */
int string_length(char *str);
int string_compare(char *str1, char *str2);
char *string_starts_with(const char *haystack, const char *needle);
char *string_concatenate(char *destination, char *source);

/* string1.c */
char *_copy_string(char *dest, char *src);
char *_duplicate_string(const char *str);
void _print_string(char *str);
int _put_character(char c);


/* shloop.c */
int shell_loop(info_t *info, char **av);
int find_builtin_command(info_t *info);
void find_command(info_t *info);
void fork_command(info_t *info);

/* parser.c */
int is_executable(info_t *info, char *path);
char *duplicate_chars(char *str, int start, int stop);
char *find_cmd_path(info_t *info, char *pathstr, char *cmd);

/* loophsh.c */
int loophsh(char **);


#endif
