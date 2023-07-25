#include "shell.h"
/**
 *source - cotrols and parses the input
 *@shell: the main struct
 *@line: the input
 *Return: 0 incase of command exit else 1
 */

int source(SHELL *shell, char *line)
{
	log *head, *current;
	char *word, *copy;
	int result;

	head = NULL, copy = Strdup(line), word = strtok(copy, "|&;\n");

	while (word)
	{
		Log(&head, word), word = strtok(NULL, "|&;\n");
	}
	seperator(&head, line),	current = head;
	while (current)
	{
		shell->toks = tokenize(current->com, 1), env_extract(shell);
		if (!shell->toks)
		{
			continue;
		}
		result = handle_builtin_commands(shell);
		if (result == 1)
		{
			free(copy), Free_log(head), Frees(shell);
			return (0);
		}
		process(shell),	En_passant(shell, &current);
		if (current)
		{
			current = current->next;
		}
		Frees(shell);
	}
	free(copy), Free_log(head);
	return (1);
}

/**
 *shuffle - swaps one of the logcal operators for non printables and back
 *@line: the input
 *@mode: 1 for swaping to non printables and 2 for the undo
 *Return: nothing
 */

void shuffle(char *line, int mode)
{
	int i;
	char a;

	if (mode == 1)
	{
		for (i = 0; line[i]; i++)
		{
			a = line[i];
			if (a == '|')
			{
				line[i] = 1, i++;
			}
			else if (a == '&')
			{
				line[i] = 2, i++;
			}
		}
	}

	else if (mode == 2)
	{
		for (i = 0; line[i]; i++)
		{
			a = line[i];
			if (a == 1)
			{
				line[i] = '|';
			}
			else if (a == 2)
			{
				line[i] = '&';
			}
		}
	}
}
/**
 *En_passant - controls logical operators according to exit status
 *@shell:  the main struct
 *@current: the logical operators linked list
 *Return: void
 */

void En_passant(SHELL *shell, log **current)
{
	char sp;
	int stat;

	stat = shell->status;
	sp = (*current)->sep;

	if (stat == 0)
	{
		if (sp == '&' || sp == ';')
		{
			return;
		}
		else if (sp == '|')
		{
			*current = (*current)->next;
		}
	}

	else if (stat != 0)
	{
		if (sp == '|' || sp == ';')
		{
			return;
		}
		else if (sp == '&')
		{
			*current = (*current)->next;
		}
	}
}
