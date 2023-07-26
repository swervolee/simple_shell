#include "shell.h"

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

/*void change_dir_command(SHELL *shell)
{
	int result;
	char cwd[1024];

	if (!shell->toks[1])
	{
		result = chdir(getenv_custom("HOME"));
	}

	else if (Strcmp(shell->toks[1], "-") == 0)
	{
		result = chdir(getenv_custom("OLDPWD"));
	}

	else
	{
		result = chdir(shell->toks[1]);
	}

	if (result == -1)
	{
		perror(shell->av[0]);
		return;
	}

	else if (result != -1)
	{
		getcwd(cwd, sizeof(cwd));
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", cwd, 1);
	}
	}*/


void change_dir_command(SHELL *shell) {
	int result;
	char cwd[1024];
	const char *oldpwd;

	if (!shell->toks[1] || Strcmp(shell->toks[1], "~") == 0)
	{
		result = chdir(getenv_custom("HOME"));
	}
	else if (Strcmp(shell->toks[1], "-") == 0)
	{
		oldpwd = getenv_custom("OLDPWD");
		if (oldpwd[0] == '\0')
		{
			perror("hsh");
			return;
		}
		result = chdir(oldpwd);
	}
	else
	{
		result = chdir(shell->toks[1]);
	}

	if (result == -1)
	{
		perror(shell->av[0]);
		return;
	}
	else if (result != -1)
	{
		getcwd(cwd, sizeof(cwd));
		setenv("OLDPWD", getenv_custom("PWD"), 1);
		setenv("PWD", cwd, 1);
	}
}
