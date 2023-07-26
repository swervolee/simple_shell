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
