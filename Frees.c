#include "shell.h"

/**
 *Frees - frees the main struct
 *@eshell: the main struct
 *Return: void
 */

void Frees(SHELL *eshell)
{
	int j;

	if (eshell->toks)
	{
		for (j = 0; eshell->toks[j]; j++)
		{
			free(eshell->toks[j]);
		}

		free(eshell->toks);
	}

	for (j = 0; eshell->_environ[j]; j++)
	{
		free(eshell->_environ[j]);
	}

	free(eshell->_environ);

	eshell->toks = NULL;
}

/**
 *Free_log - frees the logical operators linked list
 *@head: the head of the liked list
 *Return: void
 */

void Free_log(log *head)
{
	log *current, *tmp;

	if (head == NULL)
	{
		return;
	}

	current = head;

	while (current)
	{
		free(current->com);
		tmp = current->next;
		free(current);
		current = tmp;
	}
}
