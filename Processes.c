#include "shell.h"


int executables(char *input)
{
	char *check = input;
	int i;
	struct stat Stat;

	for (i = 0; check[i]; i++)
	{
		if (check[i] == '.')
		{
			if (check[i + 1] == '.')
				return 0;
			else if (check[i + 1] == '/')
				continue;
		}
		else if (check[i] == '/' && i != 0)
		{
			if (check[i + 1] == '.')
				continue;

			i++;
			break;
		}
		else
			break;
	}

	if (i == 0)
		return 0;

	if (stat(input + i, &Stat) == 0)
		return (i);

	return (-1);
}





char *Which(char *input)
{
	char *path, *copy, *tok;
	char *dir;
	int string_len;
	struct stat Stat;

	path = Strdup(getenv_custom("PATH"));
	copy = path;

	tok = _strtok(copy, ":");

	while (tok)
	{
		string_len = Strlen(input) + Strlen(tok) + 2;

		dir = malloc(string_len * sizeof(char));

		if (!dir)
		{
			free(dir);
			return (NULL);
		}

		dir = Strcpy(dir, tok);
		dir = Strcat(dir, "/");
		dir = Strcat(dir, input);
		dir = Strcat(dir, "\0");

		if (stat(dir, &Stat) == 0)
		{
			free(path);
			return (dir);
		}

		else
		{
			free(dir);
			tok = _strtok(NULL, ":");
		}
	}

	if (stat(input, &Stat) == 0)
	{
		free(path);
		return (Strdup(input));
	}

	free(path);
	return (NULL);
}



int Access(char *input, SHELL *shell)
{
	if (input == NULL)
	{
		/*print error to the console*/
		Command_unfound(shell);
		shell->status = 127;
		return (-1);
	}

	else if (access(input, X_OK) == -1)
	{
		/*print error to the console*/
		path_error(shell);
		return (-1);
	}

	return (0);
}
