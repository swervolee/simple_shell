#include "shell.h"

/**
 *handle_file - handles commands in a file
 *@shell: main struct
 *Return: nothing
 */

void handle_file(SHELL *shell)
{
	FILE *reads;
	size_t len;
	char *line = NULL;


	reads = fopen(shell->av[1], "r");

	if (reads == NULL)
	{
		exit(EXIT_FAILURE);
	}

	while ((getline(&line, &len, reads)) != -1)
	{
		shell->loop_count++;
		source(shell, line);
	}
	if (line)
	{
		free(line);
	}

	fclose(reads);
	exit(0);
}
