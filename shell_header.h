#ifndef _SHELL_HEADER_
#define _SHELL_HEADER_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct sp_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sp_list_s
{
	char separator;
	struct sp_list_s *next;
} sp_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *shell_data);
} builtin_t;

/* lists.c */
sp_list *addseparator_node_end(sp_list **head, char sep);
void free_sp_list(sp_list **head);
line_list *addlinenode(line_list **head, char *line);
void freeline_list(line_list **head);
r_var *addVar_node(r_var **head, int lvar, char *var, int lval);
void free_Var_node(r_var **head);

/* string.c */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* memory.c */
void _memorycopy(void *dstptr, const void *ptr, unsigned int size);
void *realloc_mem_blc(void *ptr, unsigned int old_size, unsigned int new_size);
char **relc_mem(char **ptr, unsigned int old_size, unsigned int new_size);

/* string_mem.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* rev_string.c */
void rev_string(char *s);

/* syntax_err_checker.c */
int count_rep_char(char *input, int i);
int fd_syt_errors(char *input, int i, char last);
int indx_first_char(char *input, int *i);
void print_syt_error(data_shell *shell_data, char *input, int i, int bool);
int check_syntax_error(data_shell *shell_data, char *input);

/* shell_loop.c */
char *without_comment(char *in);
void shell_loop(data_shell *shell_data);

/* split.c */
char *swap_char(char *input, int bool);
void add_nodes(sp_list **head_s, line_list **head_l, char *input);
void go_next(sp_list **list_s, line_list **list_l, data_shell *shell_data);
int split_commands(data_shell *shell_data, char *input);
char **split_line(char *input);

/* rep_var.c */
void check_env(r_var **h, char *in, data_shell *data);
int check_vars(r_var **h, char *in, char *st, data_shell *data);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, data_shell *shell_data);

/* getLine.c */
void bring_line_var(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line_input(char **lineptr, size_t *n, FILE *stream);
char *read_line(int *i_eof);

/* exec_line_input.c */
int exec_line(data_shell *shell_data);

/* exec_cmd_shell.c */
int is_currdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int if_is_executable(data_shell *shell_data);
int check_error_cmd(char *dir, data_shell *shell_data);
int sh_execc(data_shell *shell_data);

/* environ.c */
char *_getenv(const char *name, char **_environ);
int _env(data_shell *shell_data);
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, data_shell *shell_data);
int _setenv(data_shell *shell_data);
int _unsetenv(data_shell *shell_data);

/* change_dir_shell.c */
void cd_p_dir(data_shell *shell_data);
void cd_dir_ag(data_shell *shell_data);
void previous_cdir(data_shell *shell_data);
void cd_dir_ag_home(data_shell *shell_data);

/* shell_exits.c */
int exit_shell(data_shell *shell_data);

/* string_mani.c */
int getLength(int n);
char *sh_itoa(int n);
int _atoi(char *s);

/* error_handle1.c */
char *strcat_cd(data_shell *, char *, char *, char *);
char *err_get_cd(data_shell *shell_data);
char *err_not_found(data_shell *shell_data);
char *err_exit_shell(data_shell *shell_data);

/* error_handle2.c */
char *error_get_alias(char **args);
char *err_env(data_shell *shell_data);
char *error_syntax(char **args);
char *error_permission(char **args);
char *err_path_126(data_shell *shell_data);

/* Builtin.c */
int getError_Builtin(data_shell *shell_data, int eval);
int getHelp_mgs_builtin(data_shell *shell_data);
int (*getBuiltin(char *cmd))(data_shell *shell_data);
int shell_cd(data_shell *shell_data);

/* Signal_handle.c */
void get_Signal(int sig);

/* help.c */
void help_envirn(void);
void help_setenv(void);
void help_unsetenv(void);
void help_general(void);
void help_exit(void);
void aux_help(void);
void help_alias(void);
void help_cd(void);

#endif
