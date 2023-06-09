#include "shell_header.h"

/**
 * strcat_cd - function that concatenates the message for cd error
 *
 * @shell_data: data relevant (directory)
 * @msg: message to print
 * @error: output message
 * @ver_str: counter lines
 * Return: error message
 */
char *strcat_cd(data_shell *shell_data, char *msg, char *error, char *ver_str)
{
	char *illegal_flag;

	_strcpy(error, shell_data->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, shell_data->args[0]);
	_strcat(error, msg);
	if (shell_data->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = shell_data->args[1][1];
		illegal_flag[2] = '\0';
		_strcat(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_strcat(error, shell_data->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * err_get_cd - error message for cd command in get_cd
 * @shell_data: data relevant (directory)
 * Return: Error message
 */
char *err_get_cd(data_shell *shell_data)
{
	int length, len_id;
	char *error, *ver_str, *msg;

	ver_str = sh_itoa(shell_data->counter);
	if (shell_data->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(shell_data->args[1]);
	}

	length = _strlen(shell_data->av[0]) + _strlen(shell_data->args[0]);
	length += _strlen(ver_str) + _strlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = strcat_cd(shell_data, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * err_not_found - generic error message for command not found
 * @shell_data: data relevant (counter, arguments)
 * Return: Error message
 */
char *err_not_found(data_shell *shell_data)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = sh_itoa(shell_data->counter);
	length = _strlen(shell_data->av[0]) + _strlen(ver_str);
	length += _strlen(shell_data->args[0]) + 16;
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
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * err_exit_shell - generic error message for exit in get_exit
 * @shell_data: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *err_exit_shell(data_shell *shell_data)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = sh_itoa(shell_data->counter);
	length = _strlen(shell_data->av[0]) + _strlen(ver_str);
	length += _strlen(shell_data->args[0]) + _strlen(shell_data->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, shell_data->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, shell_data->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, shell_data->args[1]);
	_strcat(error, "\n\0");
	free(ver_str);

	return (error);
}
