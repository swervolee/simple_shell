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
					exit_status = atoi(shell->toks[1]);
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
		exit_status = atoi(shell->toks[1]);
		shell->status = exit_status;
		exit(shell->status);
	}
	else
	{
		shell->status = 0;
		exit(shell->status);
	}
}

void change_dir_command(SHELL *shell)
{
	int result, printed = 0;
	char *cwd, *old_pwd;
	char *dir = shell->toks[1];

	if (!dir || Strcmp(dir, "~") == 0)
		dir = getenv_custom("HOME", shell);
	else if (Strcmp(dir, "-") == 0)
	{
		dir = getenv_custom("OLDPWD", shell);
		if (dir)
		{
			write(STDOUT_FILENO, dir, strlen(dir));
			write(STDOUT_FILENO, "\n", 1);
			printed = 1;
		}
		else
		{
			write(STDERR_FILENO, "cd: OLDPWD not set\n", 19);
			return;
		}
	}
	old_pwd = malloc(64 *sizeof(char));
	if (old_pwd)
	{
		if (getcwd(old_pwd, 64) != NULL)
		{
			result = chdir(dir);
			if (result == 0)
			{
				cwd = malloc(64 *sizeof(char));
				if (cwd)
				{
					if (getcwd(cwd, 64) != NULL)
					{
						setenv("PWD", cwd, 1);
						setenv("OLDPWD", old_pwd, 1);
						if (!printed)
						{
							write(STDOUT_FILENO, cwd, strlen(cwd));
							write(STDOUT_FILENO, "\n", 1);
						}
					}
					else
						write(STDERR_FILENO, "getcwd error\n", 13);
					free(cwd);
				}
				else
					write(STDERR_FILENO, "malloc error\n", 13);
			}
			else
				write(STDERR_FILENO, "chdir error\n", 12);
		}
		else
			write(STDERR_FILENO, "getcwd error\n", 13);
		free(old_pwd);
	}
	else
		write(STDERR_FILENO, "malloc error\n", 13);
}
