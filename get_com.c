#include"shell_header.h"

/**
 * get_sigint - Handle the crtl + c call in prompt
 * @sig: Signal handler
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}

/**
 * bring_line - assigns the line var for get_line
 * @lineptr: Buffer that store the input str
 * @buffer: str that is been called to line
 * @n: size of line
 * @j: size of buffer
 */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j)
{

	if (*lineptr == NULL)
	{
		if  (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * get_line - Read inpt from stream
 * @lineptr: buffer that stores the input
 * @n: size of lineptr
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	int i;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	bring_line(lineptr, n, buffer, input);
	retval = input;
	if (i != 0)
		input = 0;
	return (retval);
}

/**
 * get_help - function that retrieves help messages according builtin
 * @db_shell: data structure (args and input)
 * Return: Return 0
*/
int get_help(shell_bd *db_shell)
{

	if (db_shell->args[1] == 0)
		aux_help_general();
	else if (_strcmp(db_shell->args[1], "setenv") == 0)
		aux_help_setenv();
	else if (_strcmp(db_shell->args[1], "env") == 0)
		aux_help_env();
	else if (_strcmp(db_shell->args[1], "unsetenv") == 0)
		aux_help_unsetenv();
	else if (_strcmp(db_shell->args[1], "help") == 0)
		aux_help();
	else if (_strcmp(db_shell->args[1], "exit") == 0)
		aux_help_exit();
	else if (_strcmp(db_shell->args[1], "cd") == 0)
		aux_help_cd();
	else if (_strcmp(db_shell->args[1], "alias") == 0)
		aux_help_alias();
	else
		write(STDERR_FILENO, db_shell->args[0],
		      _strlen(db_shell->args[0]));

	db_shell->status = 0;
	return (1);
}


/**
 * get_error - calls the error according the builtin, syntax or permission
 * @db_shell: data structure that contains arguments
 * @eval: error value
 * Return: error
 */
int get_error(shell_bd *db_shell, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = get_env_errror_msg(db_shell);
		break;
	case 126:
		error = error_path_126(db_shell);
		break;
	case 127:
		error = not_found_error (db_shell);
		break;
	case 2:
		if (_strcmp("exit", db_shell->args[0]) == 0)
			error = exit_error_shell(db_shell);
		else if (_strcmp("cd", db_shell->args[0]) == 0)
			error = error_msg_cd(db_shell);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	db_shell->status = eval;
	return (eval);
}

/**
 * get_builtin - builtin that pais the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *cmd))(shell_bd*)
{
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", change_dir },
		{ "help", get_help },
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
 * read_line - reads the input string.
 *
 * @i_eof: return value of getline function
 * Return: input string
 */
char *read_line(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}

