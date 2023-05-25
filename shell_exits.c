#include "shell_header.h"

/**
 * exit_shell - exits the shell
 * @shell_data: data relevant (status and args)
 * Return: 0 on success.
 */
int exit_shell(data_shell *shell_data)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (shell_data->args[1] != NULL)
	{
		ustatus = _atoi(shell_data->args[1]);
		is_digit = _isdigit(shell_data->args[1]);
		str_len = _strlen(shell_data->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			getError_Builtin(shell_data, 2);
			shell_data->status = 2;
			return (1);
		}
		shell_data->status = (ustatus % 256);
	}
	return (0);
}
