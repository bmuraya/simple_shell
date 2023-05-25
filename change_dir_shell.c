#include "shell_header.h"

/**
 * cd_p_dir - changes to the parent directory
 *
 * @shell_data: data relevant (environ)
 *
 * Return: no return
 */
void cd_p_dir(data_shell *shell_data)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, shell_data);
	dir = shell_data->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", cp_pwd, shell_data);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, shell_data);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", shell_data);
	}
	shell_data->status = 0;
	free(cp_pwd);
}

/**
 * cd_dir_ag - changes to a directory given by the user
 *
 * @shell_data: data relevant (directories)
 * Return: no return
 */
void cd_dir_ag(data_shell *shell_data)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = shell_data->args[1];
	if (chdir(dir) == -1)
	{
		getError_Builtin(shell_data, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, shell_data);

	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir, shell_data);

	free(cp_pwd);
	free(cp_dir);

	shell_data->status = 0;

	chdir(dir);
}

/**
 * previous_cdir - changes to the previous directory
 *
 * @shell_data: data relevant (environ)
 * Return: no return
 */
void previous_cdir(data_shell *shell_data)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", shell_data->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd, shell_data);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, shell_data);
	else
		set_env("PWD", cp_oldpwd, shell_data);

	p_pwd = _getenv("PWD", shell_data->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	shell_data->status = 0;

	chdir(p_pwd);
}

/**
 * shell_cd - changes current directory
 *
 * @shell_data: data relevant
 * Return: 1 on success
 */
int shell_cd(data_shell *shell_data)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = shell_data->args[1];

	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_dir_ag_home(shell_data);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		previous_cdir(shell_data);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_p_dir(shell_data);
		return (1);
	}

	cd_dir_ag(shell_data);

	return (1);
}



/**
 * cd_dir_ag_home - changes to home directory
 *
 * @shell_data: data relevant (environ)
 * Return: no return
 */
void cd_dir_ag_home(data_shell *shell_data)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", shell_data->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, shell_data);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		getError_Builtin(shell_data, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, shell_data);
	set_env("PWD", home, shell_data);
	free(p_pwd);
	shell_data->status = 0;
}
