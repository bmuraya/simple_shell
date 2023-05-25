#include "shell_header.h"

/**
 * err_env - error message for env in get_env.
 * @shell_data: data relevant (counter, arguments)
 * Return: error message.
 */
char *err_env(data_shell *shell_data)
{
	int length;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = sh_itoa(shell_data->counter);
	msg = ": Unable to add/remove from environment\n";
	length = _strlen(shell_data->av[0]) + _strlen(ver_str);
	length += _strlen(shell_data->args[0]) + _strlen(msg) + 4;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	_strcpy(error, shell_data->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, shell_data->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(ver_str);

	return (error);
}
/**
 * err_path_126 - error message for path and failure denied permission.
 * @shell_data: data relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *err_path_126(data_shell *shell_data)
{
	int length;
	char *ver_str;
	char *error;

	ver_str = sh_itoa(shell_data->counter);
	length = _strlen(shell_data->av[0]) + _strlen(ver_str);
	length += _strlen(shell_data->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, shell_data->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, shell_data->args[0]);
	_strcat(error, ": Permission Not Allowed\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}
