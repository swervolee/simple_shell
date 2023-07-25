#include "shell.h"
/**
 *env_extract - extracts enviroment varaibles
 *@shell: the main struct
 *Return: void
 */

void env_extract(SHELL *shell)
{
	int env_count = 0, i, j;

	while (environ[env_count] != NULL)
		env_count++;
	shell->_environ = malloc(sizeof(char *) * (env_count + 1));
	if (!shell->_environ)
		return;
	for (i = 0; i < env_count; i++)
	{
		shell->_environ[i] = Strdup(environ[i]);
		if (!shell->_environ[i])
		{
			for (j = 0; j < i; j++)
				free(shell->_environ[j]);
			free(shell->_environ);
			return;
		}
	}
	shell->_environ[env_count] = NULL;
}
