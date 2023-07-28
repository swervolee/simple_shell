#include "shell.h"

/**
 *main - entry point
 *@ac: the arguement count
 *@argv: the argurment vector
 *Return: status of the exectutions
 */

int main(int ac __attribute__ ((unused)), char **argv)
{
	char *line;
	int mode = 1;
	SHELL eshell;

	eshell.av = argv;
	fill_eshell(&eshell);

	while (mode)
	{
		if (eshell.av[1])
		{
			handle_file(&eshell);
		}
		line = NULL;
		eshell.loop_count++;

		if (isatty(STDIN_FILENO))
			Write("<TINKER> ");

		line = Getline();
		line = global_var(line, &eshell);

		if (line[0] == '\0' || !line)
		{
			continue;
		}

		if (Syntax(line, &eshell) == -1)
		{
			free(line);
			continue;
		}

		mode = source(&eshell, line);
		free(line);
		line = NULL;
	}
	return (eshell.status);
}


/**
 * fill_eshell - Function that fills the struct members with respective
 * content.
 * @eshell: The struct to be filled.
 *
 * Return: Void.
 */

void fill_eshell(SHELL *eshell)
{
	eshell->pid = getpid();
	eshell->status = 0;
	eshell->_environ = NULL;
	eshell->loop_count = 0;
}


/**
 * Write - Function that writes whatver content given to the POSIX.
 * @input: Pointer to the content to be written out.
 *
 * Return: Void.
 */

void Write(char *input)
{
	int i;

	for (i = 0; input[i]; i++)
		;

	write(STDOUT_FILENO, input, i);
}
