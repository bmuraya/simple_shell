#include"shell_header.h"

/**
 * change_dir_shell
 * change_dir - changes current directory
 *
 * @db_shell: data relevant
 * Return: 1 on success
 */
int change_dir(shell_bd *db_shell)
{
	char *dir;
	int isRoot, isRoot2, isddash;

	dir = db_shell->args[1];

	if (dir != NULL)
	{
		isRoot = _strcmp("$HOME", dir);
		isRoot2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}

	if (dir == NULL || !isRoot || !isRoot2 || !isddash)
	{
		cd_to_home(db_shell);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_previous(db_shell);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		change_parent_dir(db_shell);
		return (1);
	}

	cd_to(db_shell);

	return (1);
}

/**
 * change  directory two
 *  change_parent_dir -changes to the parent directory
 *
 * @db_shell: data relevant (environ)
 *
 * Return: no return
 */
void change_parent_dir(shell_bd *db_shell)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, db_shell);
	dir = db_shell->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", cp_pwd, db_shell);
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
		set_env("PWD", cp_strtok_pwd, db_shell);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", db_shell);
	}
	db_shell->status = 0;
	free(cp_pwd);
}

/**
 * cd_to - changes to a directory given
 * by the user
 *
 * @db_shell: data relevant (directories)
 * Return: no return
 */
void cd_to(shell_bd *db_shell)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = db_shell->args[1];
	if (chdir(dir) == -1)
	{
		get_error(db_shell, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, db_shell);

	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir, db_shell);

	free(cp_pwd);
	free(cp_dir);

	db_shell->status = 0;

	chdir(dir);
}

/**
 * cd_previous - changes to the previous directory
 *
 * @db_shell: data relevant (environ)
 * Return: no return
 */
void cd_previous(shell_bd *db_shell)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", db_shell->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd, db_shell);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, db_shell);
	else
		set_env("PWD", cp_oldpwd, db_shell);

	p_pwd = _getenv("PWD", db_shell->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	db_shell->status = 0;

	chdir(p_pwd);
}

/**
 * cd_to_home - changes to home directory
 *
 * @db_shell: data relevant (environ)
 * Return: no return
 */
void cd_to_home(shell_bd *db_shell)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", db_shell->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, db_shell);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(db_shell, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, db_shell);
	set_env("PWD", home, db_shell);
	free(p_pwd);
	db_shell->status = 0;
}
