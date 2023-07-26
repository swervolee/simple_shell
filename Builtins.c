#include "shell.h"

/**
 *handle_builtin_commands - handles builtins
 *@shell: the main struct
 *Return: 1 case of exit, 0 on success and -1 for fail
 */
int handle_builtin_commands(SHELL *shell)
{
	long unsigned int i;
	int exit_status;

	builtin builtin_commands[] = {
		/*{"env", env_command},*/
		{"exit", exit_command},
		{"cd", change_dir_command}
	};

	for (i = 0; i < sizeof(builtin_commands) / sizeof(builtin); i++)
	{
		if (Strcmp(shell->toks[0], builtin_commands[i].command) == 0)
		{
			if (Strcmp(builtin_commands[i].command, "exit") == 0)
			{
				if (shell->toks[1])
				{
					exit_status = Atoi(shell->toks[1]);
					shell->status = exit_status;
				}
				else
					shell->status = 0;
				return (1);
			}
			builtin_commands[i].function(shell);
			return (0);
		}
	}
	return (-1);
}


/**
 *env_command - prints the enviroment variables
 *@shell: the mian struct
 *Return: nothing
 */
void env_command(SHELL *shell)
{
	char **_env = shell->_environ;
	while (*_env)
	{
		Write(*_env);
		Write("\n");
		_env++;
	}
}

/**
 *exit_command - exits shell
 *@shell: the main struct
 *Return: nothing
 */


void exit_command(SHELL *shell)
{
	int exit_status;

	if (shell->toks[1] != NULL)
	{
		exit_status = Atoi(shell->toks[1]);
		shell->status = exit_status;
		exit(shell->status);
	}
	else
	{
		shell->status = 0;
		exit(shell->status);
	}
}

/**
 *change_dir_command - changes directories
 *@shell: the main struct
 *Return: nothing
 */
void change_dir_command(SHELL *shell)
{
	int result;
	char cwd[1024];
	const char *oldpwd, *home;;

	if (!shell->toks[1] || Strcmp(shell->toks[1], "~") == 0)
	{
		home = getenv_custom("HOME");
		if (!home)
		{
			write(STDERR_FILENO, shell->av[0], Strlen(shell->av[0]));
			write(STDERR_FILENO, ": HOME not set\n", 15);
			return;
		}
/*		oldpwd = getenv_custom("PWD");*/
		result = chdir(home);
		oldpwd = getenv_custom("PWD");
		/*result = chdir(getenv_custom("HOME"));*/
	}
	else if (Strcmp(shell->toks[1], "-") == 0)
	{
		oldpwd = getenv_custom("OLDPWD");
		if (oldpwd[0] == '\0')
		{
			write(STDERR_FILENO, shell->av[0], Strlen(shell->av[0]));
			write(STDERR_FILENO, ": OLDPWD not set\n", 17);
			return;
		}
		result = chdir(oldpwd);
	}
	else
	{
		oldpwd = getenv_custom("PWD");
		result = chdir(shell->toks[1]);
	}

	if (result == -1)
	{
		write(STDERR_FILENO, shell->av[0], Strlen(shell->av[0]));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, shell->toks[1], Strlen(shell->toks[1]));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		return;
	}
	else if (!shell->toks[1])
		return;
	else
	{
		getcwd(cwd, sizeof(cwd));
		write(STDOUT_FILENO, cwd, Strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
		setenv("OLDPWD", getenv_custom("PWD"), 1);
		setenv("PWD", cwd, 1);
	}
}
