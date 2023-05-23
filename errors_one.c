#include"shell_header.h"

/**
 * cd_strcat - function that concatenates the message for cd error
 *
 * @db_shell: data relevant (directory)
 * @msg: message to print
 * @error: output message
 * @ver_str: counter lines
 * Return: error message
 */
char *cd_strcat(shell_bd *db_shell, char *msg, char *error, char *ver_str)
{
	char *illegal_flag;

	_strcpy(error, db_shell->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, db_shell->args[0]);
	_strcat(error, msg);
	if (db_shell->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = db_shell->args[1][1];
		illegal_flag[2] = '\0';
		_strcat(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_strcat(error, db_shell->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * error_msg_cd - error message for cd command in get_cd
 * @db_shell: data relevant (directory)
 * Return: Error message
 */
char *error_msg_cd(shell_bd *db_shell)
{
	int length, len_id;
	char *error, *ver_str, *msg;

	ver_str = aux_itoa(db_shell->counter);
	if (db_shell->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(db_shell->args[1]);
	}

	length = _strlen(db_shell->av[0]) + _strlen(db_shell->args[0]);
	length += _strlen(ver_str) + _strlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = cd_strcat(db_shell, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * not_found_error  - generic error message for command not found
 * @db_shell: data relevant (counter, arguments)
 * Return: Error message
 */
char *not_found_error (shell_bd *db_shell)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(db_shell->counter);
	length = _strlen(db_shell->av[0]) + _strlen(ver_str);
	length += _strlen(db_shell->args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, db_shell->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, db_shell->args[0]);
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * exit_error_shell - generic error message for exit in get_exit
 * @db_shell: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *exit_error_shell(shell_bd *db_shell)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(db_shell->counter);
	length = _strlen(db_shell->av[0]) + _strlen(ver_str);
	length += _strlen(db_shell->args[0]) + _strlen(db_shell->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, db_shell->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, db_shell->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, db_shell->args[1]);
	_strcat(error, "\n\0");
	free(ver_str);

	return (error);
}


/**
 * Errors two
 * get_env_errror_msg - error message for env in get_env.
 * @db_shell: data relevant (counter, arguments)
 * Return: error message.
 */
char *get_env_errror_msg(shell_bd *db_shell)
{
	int length;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = aux_itoa(db_shell->counter);
	msg = ": Unable to add/remove from environment\n";
	length = _strlen(db_shell->av[0]) + _strlen(ver_str);
	length += _strlen(db_shell->args[0]) + _strlen(msg) + 4;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	_strcpy(error, db_shell->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, db_shell->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(ver_str);

	return (error);
}
/**
 * error_path_126 - error message for path and failure denied permission.
 * @db_shell: data relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *error_path_126(shell_bd *db_shell)
{
	int length;
	char *ver_str;
	char *error;

	ver_str = aux_itoa(db_shell->counter);
	length = _strlen(db_shell->av[0]) + _strlen(ver_str);
	length += _strlen(db_shell->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, db_shell->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, db_shell->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}
