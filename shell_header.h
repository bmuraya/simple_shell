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
} shell_bd;

/**
 * struct separatorlist_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct separatorlist_s
{
	char separator;
	struct separatorlist_s *next;
} separatorlist;

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
 * struct r_var_list -single linked list
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
	int (*f) (shell_bd *db_shell) ;
} builtin_t;

/* aux_lists.c */
separatorlist *addseparator_node_end(separatorlist **head, char sep);
void free_separatorlist(separatorlist **head);
line_list *addline_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/* aux_lists2.c */
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head) ;

/* aux_str functions */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* aux_mem.c */
void _memorycopy(void *_Destptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* aux_str2.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* aux_str3.c */
void rev_string(char *s);

/* check_syntax_error.c */
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(shell_bd *db_shell, char *input, int i, int bool);
int check_syntax_error(shell_bd *db_shell, char *input);

/* shell_loop.c */
char *without_comment(char *in);
void shell_loop(shell_bd *db_shell);

/* read_line.c */
char *read_line(int *i_eof);

/* split.c */
char *swap_char(char *input, int bool);
void add_nodes(separatorlist **head_s, line_list **head_l, char *input);
void go_next(separatorlist **list_s, line_list **list_l, shell_bd *db_shell);
int split_commands(shell_bd *db_shell, char *input);
char **split_line(char *input);

/* rep_var.c */
void check_env(r_var **h, char *in, shell_bd *data);
int check_vars(r_var **h, char *in, char *st, shell_bd *data);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, shell_bd *db_shell);

/* get_line.c */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* exec_line */
int exec_line(shell_bd *db_shell);

/* cmd_exec.c */
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(shell_bd *db_shell);
int check_error_cmd(char *dir, shell_bd *db_shell);
int cmd_exec(shell_bd *db_shell);

/* env1.c */
char *_getenv(const char *name, char **_environ);
int _env(shell_bd *db_shell);

/* env2.c */
char *copyinfo(char *name, char *value);
void set_env(char *name, char *value, shell_bd *db_shell);
int _setenv(shell_bd *db_shell);
int _unsetenv(shell_bd *db_shell);

/* cd.c */
void change_parent_dir(shell_bd *db_shell);
void cd_to(shell_bd *db_shell);
void cd_previous(shell_bd *db_shell);
void cd_to_home(shell_bd *db_shell);

/* change_dir.c */
int change_dir(shell_bd *db_shell);

/* get_builtin */
int (*get_builtin(char *cmd))(shell_bd *db_shell);

/* _exit.c */
int exit_shell(shell_bd *db_shell);

/* aux_stdlib.c */
int get_len(int n);
char *aux_itoa(int n);
int _atoi(char *s);

/* aux_error1.c */
char *cd_strcat(shell_bd *, char *, char *, char *);
char *error_msg_cd(shell_bd *db_shell);
char *not_found_error (shell_bd *db_shell);
char *exit_error_shell(shell_bd *db_shell);

/* aux_error2.c */
char *error_get_alias(char **args);
char *get_env_errror_msg(shell_bd *db_shell);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(shell_bd *db_shell);


/* get_error.c */
int get_error(shell_bd *db_shell, int eval);

/* get_sigint.c */
void get_sigint(int sig);

/* aux_help.c */
void aux_help_env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_general(void);
void aux_help_exit(void);

/* aux_help2.c */
void aux_help(void);
void aux_help_alias(void);
void aux_help_cd(void);

/* get_help.c */
int get_help(shell_bd *db_shell);

#endif
