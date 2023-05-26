#include "shell_header.h"
/**
 * comp_env_var - compares env variables names
 * with the name passed.
 * @name_environ: name of the environment variable
 * @name: name passed
 * Return: 0 if are not equal. Another value if they are.
 */
int comp_env_var(const char *name_environ, const char *name)
{
	int i;

	for (i = 0; name_environ[i] != '='; i++)
	{
		if (name_environ[i] != name[i])
		{
			return (0);
		}
	}
	return (i + 1);
}
/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int i, mov;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	mov = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (i = 0; _environ[i]; i++)
	{
		/* If name and env are equal */
		mov = comp_env_var(_environ[i], name);
		if (mov)
		{
			ptr_env = _environ[i];
			break;
		}
	}
	return (ptr_env + mov);
}
/**
 * _env - prints the evironment variables
 * @shell_data: data relevant.
 * Return: 1 on success.
 */
int _env(data_shell *shell_data)
{
	int i, j;

	for (i = 0; shell_data->_environ[i]; i++)
	{

		for (j = 0; shell_data->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, shell_data->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	shell_data->status = 0;
	return (1);
}
/**
 * copy_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 * Return: new env or alias.
 */
char *copy_info(char *name, char *value)
{
char *new;
int len_name, len_value, len;

len_name = _strlen(name);
len_value = _strlen(value);
len = len_name + len_value + 2;
new = malloc(sizeof(char) * (len));
_strcpy(new, name);
_strcat(new, "=");
_strcat(new, value);
_strcat(new, "\0");
return (new);
}
