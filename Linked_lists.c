#include "shell.h"


void Log(log **head, char *command)
{
	log *current, *new;


	new = malloc(sizeof(log));

	new->com = Strdup(command);
	new->sep = 'a';
	new->next = NULL;

	if (*head == NULL)
	{
		*head = new;
		return;
	}

	current = *head;

	while (current->next != NULL)
	{
		current = current->next;
	}

	current->next = new;
	return;
}


void seperator(log **head,char *line)
{
	int i;
	log *current;
	char a;


	shuffle(line, 1);
	current = *head;

	for (i = 0; line[i]; i++)
	{
		a = line[i];

		if (a == '|')
		{
			current->sep = '|';
			current = current->next;
		}

		else if (a == '&')
		{
			current->sep = '&';
			current = current->next;
		}

		else if (a == ';')
		{
			current->sep = ';';
			current = current->next;
		}

	}

	shuffle(line, 2);
}
