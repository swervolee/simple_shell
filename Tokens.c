#include "shell.h"

#define ARRAY_SIZE 128

/**
 * tokenize - Split a line into tokens based on the specified mode.
 * @line: The line to be tokenized.
 * @mode: the mode of tokenization ie 1 for normal, 2 for special
 * characters.
 *
 * Return: A dynamically allocated array of strings containing the tokens,
 * or NULL if an error occured.
 */

char **tokenize(char *line, int mode)
{
	char **word_t, *word;
	int size = ARRAY_SIZE, i = 0;
	char *Del;

	if (line == NULL)
	{
		perror("hsh");
		return (NULL);
	}
	if (mode == 1)
	{
		Del = " \n";
	}
	else
	{
		Del = "|&;";
	}
	word_t = malloc(size * sizeof(char *));
	if (word_t == NULL)
	{
		free(word_t);
		return (NULL);
	}
	word = strtok(line, Del);
	while (word != NULL)
	{
		if (i == size - 1)
		{
			word_t = Realloc(word_t, size * sizeof(char *), size * 2 * sizeof(char *));
			if (!word_t)
			{
				write(STDERR_FILENO, "MEMORY ALLOCATION ERROR\n", 24);
				exit(EXIT_FAILURE);
			}
			size = size * 2;
		}
		word_t[i] = strdup(word), word = strtok(NULL, Del), i++;
	}
	word_t[i] = NULL;
	return (word_t);
}
