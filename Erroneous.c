#include "shell.h"

/**
 *Command_unfound -  prints the command unfoud error
 *@shell: the main struct
 *Return: nothing
 */

void Command_unfound(SHELL *shell)
{
	char *loop_count;

	loop_count = Itoa(shell->loop_count);
	Write(shell->av[0]);
	Write(": ");
	Write(loop_count);
	Write(": ");
	Write(shell->toks[0]);
	Write(": not found\n");

	free(loop_count);
}

/**
 *path_error - prints the path error
 *@shell: the main struct
 *Return: nothing
 */

void path_error(SHELL *shell)
{
	char *loop_count;


	loop_count = Itoa(shell->loop_count);

	Write(shell->av[0]);
	Write(": ");
	Write(loop_count);
	Write(": ");
	Write(shell->toks[0]);
	Write(": Permission denied\n");

	free(loop_count);
}

/**
 *write_error - writes error to thr console
 *@error: the errror to be printed
 *@shell: the main struct
 *Return: nothhig
 */

void write_error(char *error, SHELL *shell)
{
	char *count = Itoa(shell->loop_count);

	Write(shell->av[0]);
	Write(": ");
	Write(count);
	Write(": ");
	Write("Syntax error");
	Write(": \"");
	Write(error);
	Write("\" unexpected\n");

	free(count);
}
