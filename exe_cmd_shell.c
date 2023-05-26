#include "shell_header.h"

/**
 *  sh_execc - executes command lines
 *
 * @shell_data: data relevant (args and input)
 * Return: 1 on success.
 */
int sh_execc(data_shell *shell_data)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = if_is_executable(shell_data);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _which(shell_data->args[0], shell_data->_environ);
		if (check_error_cmd(dir, shell_data) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _which(shell_data->args[0], shell_data->_environ);
		else
			dir = shell_data->args[0];
		execve(dir + exec, shell_data->args, shell_data->_environ);
	}
	else if (pd < 0)
	{
		perror(shell_data->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	shell_data->status = state / 256;
	return (1);
}


/**
 *  if_is_executable - determines if is an executable
 *
 * @shell_data: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int if_is_executable(data_shell *shell_data)
{
	struct stat st;
	int i;
	char *input;

	input = shell_data->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	getError_Builtin(shell_data, 127);
	return (-1);
}

/**
 *  is_currdir - checks ":" if is in the current directory.
 * @path: type char pointer char.
 * @i: type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int is_currdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 *  _which - locates a command
 *
 * @cmd: command name
 * @_environ: environment variable
 * Return: location of the command.
 */
char *_which(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_currdir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}


/**
 *  check_error_cmd - verifies if user has permissions to access
 *
 * @dir: destination directory
 * @shell_data: data structure
 * Return: 1 if there is an error, 0 if not
 */
int check_error_cmd(char *dir, data_shell *shell_data)
{
	if (dir == NULL)
	{
		getError_Builtin(shell_data, 127);
		return (1);
	}

	if (_strcmp(shell_data->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			getError_Builtin(shell_data, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(shell_data->args[0], X_OK) == -1)
		{
			getError_Builtin(shell_data, 126);
			return (1);
		}
	}

	return (0);
}
