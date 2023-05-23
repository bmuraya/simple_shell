#include "shell_header.h"

/**
 * data_free -frees Data-structure
 *
 * @db_shell: Data-structure
 * Return: no return
 */
void data_free(shell_bd *db_shell)
{
	unsigned int i;
	 i=0 ;

	while (db_shell->_environ[i])
	{
		free(db_shell->_environ[i]);
		 i++;
	}

	free(db_shell->_environ);
	free(db_shell->pid);
}

/**
 * data_set -Initialize Data-structure
 *
 * @db_shell: Data-structure
 * @av: argv
 * Return: no return
 */
void data_set ( shell_bd *db_shell,  char **av)
{
	unsigned int i;

	db_shell->av = av; 
	db_shell->status = 0;
	 db_shell->counter = 1;
	db_shell->input = NULL;
	 db_shell->args = NULL; 
	 


	for (i = 0; environ[i]; i++)
		;

	db_shell->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		db_shell->_environ[i] = _strdup(environ[i]);
	}

	db_shell->_environ[i] = NULL;
	db_shell->pid = aux_itoa(getpid()) ;
}

/**
 * main -Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	shell_bd db_shell;
	(void) ac;

	signal(SIGINT, get_sigint);

	data_set(&db_shell, av);
	shell_loop(&db_shell);
	data_free(&db_shell);
	if (db_shell.status < 0)
		return (255); 
	return (db_shell.status);
}

