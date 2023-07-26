#include "shell.h"

int modify_env_var(const char *name, const char *value, char ***environ)
{
	char **env_var_ptr = *environ;
	char *env_var, *new_var;
	size_t name_len = my_strlen(name);

	while (*env_var_ptr)
	{
		env_var = *env_var_ptr;
		if (strncmp(env_var, name, name_len) == 0 && env_var[name_len] == '=')
		{
			new_var = malloc(name_len + my_strlen(value) + 2);
			if (new_var == NULL)
			{
				write(STDERR_FILENO, "Memory allocation error\n", 24);
				return (-1);
			}
			Strcpy(new_var, name);
			Strcat(new_var, "=");
			Strcat(new_var, value);

			free(*env_var_ptr);
			*env_var_ptr = new_var;

			return (0);
		}
		env_var_ptr++;
	}
	return (-1);
}

int add_env_var(const char *name, const char *value, SHELL *shell)
{
	int env_count = 0, i;
	char **new_environ, *new_var;
	size_t name_len;

	while (shell->_environ[env_count])
	{
		env_count++;
	}
	new_environ = malloc((env_count + 2) * sizeof(char *));
	if (!new_environ)
	{
		write(STDERR_FILENO, "Memory allocation error\n", 24);
		return (-1);
	}
	for (i = 0; i < env_count; i++)
	{
		new_environ[i] = shell->_environ[i];
	}
	name_len = my_strlen(name);
	new_var = malloc(name_len + my_strlen(value) + 2);
	if (!new_var)
	{
		write(STDERR_FILENO, "Memory allocation error\n", 24);
		free(new_environ);
		return (-1);
	}
	Strcpy(new_var, name);
	Strcat(new_var, "=");
	Strcat(new_var, value);

	new_environ[env_count] = new_var;
	new_environ[env_count + 1] = NULL;

	free(shell->_environ);
	shell->_environ = new_environ;

	return (0);
}

void setenv_command(SHELL *shell)
{
	const char *name;
	const char *value;

	if (shell->toks[1] == NULL || shell->toks[2] == NULL)
	{
/*		write(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n", 28);*/
		shell->status = -1;
		return;
	}
	name = shell->toks[1];
	value = shell->toks[2];

	if (modify_env_var(name, value, &(shell->_environ)) == 0)
	{
		shell->status = 0;
		return;
	}
	if (add_env_var(name, value, shell) == 0)
	{
		shell->status = 0;
		return;
	}
	shell->status = -1;
}
