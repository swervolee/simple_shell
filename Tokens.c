#include "shell.h"

#define ARRAY_SIZE 128


char** tokenize(char* line, int mode)
{
	char** word_token, *word;
	int size = ARRAY_SIZE, i = 0;
	char *Del;

	if (line == NULL)
	{
		perror("hsh");
		return NULL;
	}

	if (mode == 1)
	{
		Del = " \n";
	}

	else
	{
		Del = "|&;";
	}

	word_token = malloc(size * sizeof(char*));

	if (word_token == NULL)
	{
		free(word_token);
		return NULL;
	}

	word = strtok(line, Del);

	while (word != NULL)
	{
		if (i == size - 1)
		{
			word_token = Realloc(word_token, size * sizeof(char*), size * 2 * sizeof(char*));
			if (!word_token)
			{
				write(STDERR_FILENO, "MEMORY ALLOCATION ERROR\n", 24);
				exit(EXIT_FAILURE);
			}
			size = size * 2;
		}

		word_token[i] = strdup(word);
		word = strtok(NULL, Del);
		i++;
	}

	word_token[i] = NULL;

	return word_token;
}
