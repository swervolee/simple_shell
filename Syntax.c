#include "shell.h"


int Syntax(char *input, SHELL *shell)
{
	if (First(input, shell) == -1 || Syntax_error(input, shell) == -1)
	{
		return (-1);
	}

	return (0);

}



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

			else if (input[i + 1]== '&')
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

			else if (input[i + 1]== '|')
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
