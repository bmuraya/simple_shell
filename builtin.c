#include "shell_header.h"

/**
 * getHelp_mgs_builtin - a function that retrieves
 *       help messages according builtin
 * @shell_data: data structure (args and input)
 * Return: Return 0
*/
int getHelp_mgs_builtin(data_shell *shell_data)
{

	if (shell_data->args[1] == 0)
		help_general();
	else if (_strcmp(shell_data->args[1], "setenv") == 0)
		help_setenv();
	else if (_strcmp(shell_data->args[1], "env") == 0)
		help_envirn();
	else if (_strcmp(shell_data->args[1], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(shell_data->args[1], "help") == 0)
		aux_help();
	else if (_strcmp(shell_data->args[1], "exit") == 0)
		help_exit();
	else if (_strcmp(shell_data->args[1], "cd") == 0)
		help_cd();
	else if (_strcmp(shell_data->args[1], "alias") == 0)
		help_alias();
	else
		write(STDERR_FILENO, shell_data->args[0],
		      _strlen(shell_data->args[0]));

	shell_data->status = 0;
	return (1);
}

/**
 * getBuiltin - builtin that pais the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*getBuiltin(char *cmd))(data_shell *)
{
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", shell_cd },
		{ "help", getHelp_mgs_builtin },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, cmd) == 0)
			break;
	}

	return (builtin[i].f);
}

/**
 *  getError_Builtin - calls the error according
 *  the builtin, syntax or permission
 * @shell_data: data structure that contains arguments
 * @eval: error value
 * Return: error
 */
int getError_Builtin(data_shell *shell_data, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = err_env(shell_data);
		break;
	case 126:
		error = err_path_126(shell_data);
		break;
	case 127:
		error = err_not_found(shell_data);
		break;
	case 2:
		if (_strcmp("exit", shell_data->args[0]) == 0)
			error = err_exit_shell(shell_data);
		else if (_strcmp("cd", shell_data->args[0]) == 0)
			error = err_get_cd(shell_data);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	shell_data->status = eval;
	return (eval);
}
