#include "shell_header.h"

/**
 * data_free - frees data structure
 * @shell_data: data structure
 * Return: no return
 */
void data_free(data_shell *shell_data)
{
	unsigned int i;

	i = 0;

	while (shell_data->_environ[i])
	{
		free(shell_data->_environ[i]);
		i++;
	}
	free(shell_data->_environ);
	free(shell_data->pid);
}

/**
 * data_set -data structure
 * @shell_data: data structure
 * @av: argv
 * Return: no return
 */
void data_set(data_shell *shell_data, char **av)
{
	unsigned int i = 0;

	shell_data->av = av;
	shell_data->input = NULL;
	shell_data->args = NULL;
	shell_data->status = 0;
	shell_data->counter = 1;

	while (environ[i])
		i++;

	shell_data->_environ = malloc(sizeof(char *) * (i + 1));

	i = 0;
	while (environ[i])
	{
		shell_data->_environ[i] = _strdup(environ[i]);
		i++;
	}

	shell_data->_environ[i] = NULL;
	shell_data->pid = sh_itoa(getpid());
}

/**
 * main - Entry point
 * @ac:argc
 * @av:argv
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	data_shell shell_data;
	(void)ac;

	signal(SIGINT, get_Signal);
	data_set(&shell_data, av);
	shell_loop(&shell_data);
	data_free(&shell_data);
	if (shell_data.status < 0)
		return (255);
	return (shell_data.status);
}
