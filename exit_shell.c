#include"shell_header.h"

/**
 * exit_shell - exits the shell
 *
 * @db_shell: data relevant (status and args)
 * Return: 0 on success.
 */
int exit_shell(shell_bd *db_shell)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (db_shell->args[1] != NULL)
	{
		ustatus = _atoi(db_shell->args[1]);
		is_digit = _isdigit(db_shell->args[1]);
		str_len = _strlen(db_shell->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			get_error(db_shell, 2);
			db_shell->status = 2;
			return (1);
		}
		db_shell->status = (ustatus % 256);
	}
	return (0);
}
