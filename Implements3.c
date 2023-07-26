#include "shell.h"

/**
 *Atoi- changes as tring to int
 *@nptr: the string number
 *Return: the int
 */
int Atoi(const char *nptr)
{
	int result = 0, sign = 1, i = 0;

	if (nptr[0] == '-')
	{
		sign = -1;
		i = 1;
	}
	while (nptr[i] != '\0')
	{
		if (nptr[i] >= '0' && nptr[i] <= '9')
		{
			result = result * 10 + (nptr[i] - '0');
			i++;
		}
		else
		{
			return (0);
		}
	}
	return (sign * result);
}
/**
 * Strlen - function that counts the number of characters in a given string.
 * @input: Pointer to the string whose characters are to be counted.
 *
 * Return: The number of character counted in the string.
 **/

int Strlen(char *input)
{
	int i;

	for (i = 0; input[i]; i++)
		;
	return (i);
}


/**
 *extension - an extesnion for strtok
 *@nextToken: the next token
 *@delim: the delimiters used
 *@isDelimiter: a tracker for the delimiters
 *Return: nothing
 */

void extension(char *nextToken, const char *delim, int *isDelimiter)
{
	int i;

	for (i = 0; delim[i] != '\0'; i++)
	{
		if (*nextToken == delim[i])
		{
			*isDelimiter = 1;
			break;
		}
	}
}
