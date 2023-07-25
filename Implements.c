#include "shell.h"

#define buffsize 1024


void *Realloc(void *ptr, size_t old_size, size_t size)
{
	void *new_ptr;
	char *old_ptr = (char *)ptr;
	char *new_char_ptr;
	size_t i;


	if (!ptr)
	{
		return malloc(size);
	}
	else if (size == 0)
	{
		free(ptr);
		return NULL;
	}
	else
	{
		new_ptr = malloc(size);
		if (!new_ptr)
		{
			return NULL;
		}

		if (size < old_size)
		{
			old_size = size;
		}

		new_char_ptr = (char *)new_ptr;

		for (i = 0; i < old_size; i++)
		{
			new_char_ptr[i] = old_ptr[i];
		}

		free(ptr);

		return new_ptr;
	}
}




char *Getline()
{
	char *buffer, r = 0;
	int i = 0, charsRead, buffer_size;

	buffer_size = buffsize;
	buffer = malloc(buffer_size * sizeof(char));

	if (buffer == NULL)
	{
		free(buffer);
		return (NULL);
	}

	while(r != EOF && r != '\n')
	{
		fflush(stdin);

		charsRead = read(STDIN_FILENO, &r, 1);


		if (charsRead == 0)
		{
			free(buffer);
			exit(EXIT_SUCCESS);
		}

		buffer[i] = r;

		if (buffer[0] == '\n')
		{
			free(buffer);
			return ("\0");
		}

		i++;
	}

	if (r == EOF)
	{
		Write("\n");
	}

	buffer[i] = '\0';
	buffer = hash(buffer);

	if (buffer == NULL)
	{
		return ("\0");
	}

	return (buffer);
}



char *hash(char* buffer)
{
	int i;
	bool quotes = false;

	if (buffer[0] == '#')
	{
		free(buffer);
		return (NULL);
	}

	else
	{
		for (i = 0; buffer[i]; i++)
		{
			if (buffer[i] == 34)
			{
				quotes = !quotes;
			}

			if (!quotes && buffer[i] == '#' && buffer[i - 1] == ' ')
			{
				buffer[i] = '\0';
				break;
			}
		}
	}

	return buffer;
}


char* _strtok(char *str, const char *delim)
{
	static char *nextToken = NULL;
	char *token = NULL;
	int isDelimiter;
	size_t i;

	if (str != NULL)
	{
		nextToken = str;
	}

	if (nextToken == NULL || *nextToken == '\0')
	{
		return NULL;
	}

	while (*nextToken != '\0')
	{
		isDelimiter = 0;

		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*nextToken == delim[i])
			{
				isDelimiter = 1;
				break;
			}
		}

		if (!isDelimiter)
		{
			break;
		}

		nextToken++;
	}

	if (*nextToken == '\0')
	{
		return NULL;
	}

	token = nextToken;

	while (*nextToken != '\0')
	{
		isDelimiter = 0;

		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*nextToken == delim[i])
			{
				isDelimiter = 1;
				break;
			}
		}

		if (isDelimiter)
		{
			*nextToken = '\0';
			nextToken++;
			break;
		}

		nextToken++;
	}

	return token;
}


/**
 * getenv_custom - gets environment variables
 * @name: name of the variable
 * @shell_s: struct to store environment variables
 * Return:
 *
char *getenv_custom(const char *name, SHELL *shell)
{
	size_t name_length = 0;
	int match;
	char **env;
	size_t i;

	if (name == NULL || *name == '\0')
	{
		return (NULL);
	}
	while (name[name_length] != '\0')
		name_length++;
	for (env = shell->_environ; *env != NULL; env++)
	{
		match = 1;
		for (i = 0; i < name_length; i++)
		{
			if ((*env)[i] != name[i])
			{
				match = 0;
				break;
			}
		}
		if (match && (*env)[name_length] == '=')
		{
			return (&(*env)[name_length + 1]);
		}
	}
	return (NULL);
}*/


char *getenv_custom(const char *name, SHELL *shell)
{
	char **copy = NULL;
	int i, j, k;

	copy = shell->_environ;

	for (i = 0; copy[i]; i++)
	{
		k = 0;
		for (j = 0; copy[i][j]; j++)
		{
			if (copy[i][j] == '=')
			{
				return (copy[i] + j + 1);
			}
			if (name[k] == copy[i][j])
			{
				k++;
			}
			else
			{
				break;
			}
		}
	}
	return (NULL);
}


int Strlen(char *input)
{
	int i;

	for (i = 0; input[i]; i++)
		;

	return (i);
}
