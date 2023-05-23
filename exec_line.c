#include"shell_header.h"

/**
 * exec_line - finds builtins and commands
 *
 * @db_shell: data relevant (args)
 * Return: 1 on success.
 */
int exec_line(shell_bd *db_shell)
{
	int (*builtin)(shell_bd *db_shell);

	if (db_shell->args[0] == NULL)
		return (1);

	builtin = get_builtin(db_shell->args[0]);

	if (builtin != NULL)
		return (builtin(db_shell));

	return (cmd_exec(db_shell));
}
