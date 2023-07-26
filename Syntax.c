#include "shell.h"

/**
 * Syntax - check the syntax of a command for correctness.
 * @input: The command to check for syntax.
 * @shell: Pointer to the shell data structure.
 *
 * Return: 0 on success, -1 if there is a syntax error.
 */

int Syntax(char *input, SHELL *shell)
{
	if (First(input, shell) == -1 || Syntax_error(input, shell) == -1)
	{
		return (-1);
	}

	return (0);

}

/**
 * First - Check the syntax of the first token in the command.
 * @input: The command to check for the first token.
 * @shell: Pointer to the shell data structure.
 *
 * Return: 1 on success, -1 if there is a syntax error.
 */

int First(char *input, SHELL *shell)
{
	int i;
	char *Error_txt = NULL;

	for (i = 0; input[i]; i++)
	{
		while (input[i] == ' ' || input[i] == '\t')
		{
			i++;
		}

		if (input[i] == ';')
		{
			Error_txt = (input[i + 1] == ';' ? ";;" : ";");
			break;
		}

		else if (input[i] == '|')
		{
			Error_txt = (input[i + 1] == '|' ? "||" :  "|");
			break;
		}

		else if (input[i] == '&')
		{
			Error_txt = (input[i + 1] == '&' ? "&&" : "&");
			break;
		}

		else
		{
			break;
		}
	}
	if (Error_txt)
	{
		write_error(Error_txt, shell);
		return (-1);
	}
	return (1);
}

/**
 * Syntax_error - Check for syntax errors in the command.
 * @input: The command to check for syntax errors.
 * @shell: Pointer to the shell data structure.
 *
 * Return: 0 on success, -1 if a syntax error is present.
 */

int Syntax_error(char *input, SHELL *shell)
{
	int i;
	char *error_txt;

	error_txt = NULL;
	i = 1;

	for (; input[i]; i++)
	{
		if (input[i] == ';')
		{
			if (input[i + 1] == ';')
			{
				error_txt = ";;";
				break;
			}

			else if (input[i + 1] == '|')
			{
				error_txt = "|";
				break;
			}

			else if (input[i + 1] == '&')
			{
				error_txt = "&";
				break;
			}
		}
	}
	if (error_txt)
	{
		write_error(error_txt, shell);
		return (-1);
	}
	else if (Pipe(input, shell) == -1 || ampersand(input, shell) == -1)
	{
		return (-1);
	}

	return (0);
}

/**
 * Pipe - Check for syntax errors retated to pipes in command.
 * @input: the command to check for pipe-related syntax errors.
 * @shell: Pointer to the shell data structure.
 *
 * Return: 0 on success, -1 if a syntax error is encountered.
 */

int Pipe(char *input, SHELL *shell)
{
	int i;
	char *error_txt = NULL;

	for (i = 1; input[i]; i++)
	{
		if (input[i] == '|' && input[i + 1] == '|')
		{
			i += 2;
		}

		if (input[i] == '|')
		{
			if (input[i + 1] == ';')
			{
				error_txt = (input[i + 2] == ';' ? ";;" : ";");
				break;
			}

			else if (input[i + 1] == '&')
			{
				error_txt = (input[i + 2] == '&' ? "&&" : "&");
				break;
			}

			else if (input[i] == '|')
			{
				i++;
				error_txt = (input[i + 1] == '|' ? "||" : "|");
				break;
			}
		}
	}

	if (error_txt)
	{
		write_error(error_txt, shell);
		return (-1);
	}

	return (0);
}

/**
 * ampersand - Check for syntax errors related to ampersands in the command.
 * @input: the command to check for ampersand-related syntax errors.
 * @shell: Pointer to the shell data structure.
 *
 * Return: 0 on success, -1 if a syntax error is encountered.
 */

int ampersand(char *input, SHELL *shell)
{
		int i;
	char *error_txt = NULL;

	for (i = 1; input[i]; i++)
	{
		if (input[i] == '&' && input[i + 1] == '&')
		{
			i += 2;
		}

		if (input[i] == '&')
		{
			if (input[i + 1] == ';')
			{
				error_txt = (input[i + 2] == ';' ? ";;" : ";");
				break;
			}

			else if (input[i + 1] == '|')
			{
				error_txt = (input[i + 2] == '|' ? "||" : "|");
				break;
			}

			else if (input[i] == '&')
			{
				i++;
				error_txt = (input[i + 1] == '&' ? "&&" : "&");
				break;
			}
		}
	}

	if (error_txt)
	{
		write_error(error_txt, shell);
		return (-1);
	}

	return (0);
}
