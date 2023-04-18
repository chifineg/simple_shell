#include "shell.h"
/**
 * execute - function to execute with entire path variables.
 * @data: program data pointer
 * Return: 0 when success, -1 when error.
 */
int execute(data_of_program *data)
{
	int x = 0, stat;
	pid_t pidd;

	x = builtins_list(data);
	if (x != -1)
		return (x);

	x = find_program(data);
	if (x)
	{
		return (x);
	}
	else
	{
		pidd = fork();
		if (pidd == -1)
		{
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{
			x = execve(data->tokens[0], data->tokens, data->env);
			if (x == -1)
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&stat);
			if (WIFEXITED(stat))
				errno = WEXITSTATUS(stat);
			else if (WIFSIGNALED(stat))
				errno = 128 + WTERMSIG(stat);
		}
	}
	return (0);
}
