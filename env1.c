#include"shell_header.h"

/**
 * compares_env_name -compares environment variables names
 * with the name passed.
 * @name_env: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int compares_env_name(const char *name_env, const char *name)
{
	int i;

	for (i = 0; name_env[i] != '='; i++)
	{
		if (name_env[i] != name[i])
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
 *
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
		mov = compares_env_name(_environ[i], name);
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
 *
 * @db_shell: data relevant.
 * Return: 1 on success.
 */
int _env(shell_bd *db_shell)
{
	int i, j;

	for (i = 0; db_shell->_environ[i]; i++)
	{

		for (j = 0; db_shell->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, db_shell->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	db_shell->status = 0;

	return (1);
}


/**
 * Env2
 * copyinfo - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: new env or alias.
 */
char *copyinfo(char *name, char *value)
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

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @db_shell: data structure (environ)
 * Return: no return
 */
void set_env(char *name, char *value, shell_bd *db_shell)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; db_shell->_environ[i]; i++)
	{
		var_env = _strdup(db_shell->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(db_shell->_environ[i]);
			db_shell->_environ[i] = copyinfo(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	db_shell->_environ = _reallocdp(db_shell->_environ, i, sizeof(char *) * (i + 2));
	db_shell->_environ[i] = copyinfo(name, value);
	db_shell->_environ[i + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @db_shell: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _setenv(shell_bd *db_shell)
{

	if (db_shell->args[1] == NULL || db_shell->args[2] == NULL)
	{
		get_error(db_shell, -1);
		return (1);
	}

	set_env(db_shell->args[1], db_shell->args[2], db_shell);

	return (1);
}

/**
 * _unsetenv - deletes a environment variable
 *
 * @db_shell: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(shell_bd *db_shell)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (db_shell->args[1] == NULL)
	{
		get_error(db_shell, -1);
		return (1);
	}
	k = -1;
	for (i = 0; db_shell->_environ[i]; i++)
	{
		var_env = _strdup(db_shell->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, db_shell->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_error(db_shell, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; db_shell->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = db_shell->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(db_shell->_environ[k]);
	free(db_shell->_environ);
	db_shell->_environ = realloc_environ;
	return (1);
}
