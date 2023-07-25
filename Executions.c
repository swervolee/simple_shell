#include "shell.h"

/**
 *process - processees the commands for forking or execution
 *@shell: the mai struct
 *Return: nothing
 */

int process(SHELL *shell)
{
	int Exec, i, numbuilts;
	char *Dir,  *bul = shell->toks[0], *builtin[] = {"cd", "exit"};

	Exec = executables(shell->toks[0]);

	numbuilts = sizeof(builtin) / sizeof(builtin[0]);
	for (i = 0; i < numbuilts; i++)
	{
		if (Strcmp(bul, builtin[i]) == 0)
			return (0);
	}
	if (Exec == -1)
	{
		Command_unfound(shell);
		shell->status = 127;
		return (1);
	}
	else if (Exec == 0)
	{
		Dir = Which(shell->toks[0]);
	}
	else
	{
		Dir = shell->toks[0] + Exec;
	}
	if (Access(Dir, shell) == -1)
	{
		shell->status = 126, free(Dir);
		return (1);
	}
	Fork(Dir, shell);
	if (Exec == 0)
	{
		free(Dir);
	}
	return (0);
}

/**
 *Fork - performs the executio of the command
 *@input: the path of the executable
 *@shell: the mai struct
 */

void Fork(char *input, SHELL *shell)
{
	pid_t Pid;
	int state;
	char **tok;


	Pid = fork();
	tok = shell->toks;

	if (Pid == 0)
	{
		execve(input, tok, environ);
	}

	else if (Pid < 0)
	{
		perror(tok[0]);
		return;
	}

	else
	{
		do {
			waitpid(Pid, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	shell->status = state / 256;
}
