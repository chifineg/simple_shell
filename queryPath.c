#include "shell.h"

int check_file(char *full_path);

/**
 * find_program - function to locate a program in path
 * @data: points to program data
 * Return: 0 when success, or errcode when error
 */

int find_program(data_of_program *data)
{
	int x = 0, y = 0;
	char **folder;

	if (!data->command_name)
		return (2);

	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (check_file(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	folder = tokenize_path(data);

	if (!folder || !folder[0])
	{
		errno = 127;
		return (127);
	}
	for (x = 0; folder[x]; x++)
	{
		folder[x] = str_concat(folder[x], data->tokens[0]);
		y = check_file(folder[x]);
		if (y == 0 || y == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(folder[x]);
			free_array_of_pointers(folder);
			return (y);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(folder);
	return (y);
}

/**
 * tokenize_path - function to tokenize path in directories
 * @data: points to program data
 * Return: directory path array
 */

char **tokenize_path(data_of_program *data)
{
	int x = 0;
	int dirCount = 2;
	char **tokenz = NULL;
	char *PATH;

	PATH = env_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = str_duplicate(PATH);

	for (x = 0; PATH[x]; x++)
	{
		if (PATH[x] == ':')
			dirCount++;
	}

	tokenz = malloc(sizeof(char *) * dirCount);

	x = 0;
	tokenz[x] = str_duplicate(_strtok(PATH, ":"));
	while (tokenz[x++])
	{
		tokenz[x] = str_duplicate(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokenz);

}

/**
 * check_file - function to check if a file exists,
 * checks if it is not a directory and
 * if it has excecution permisions.
 * @full_path: points to file's full name
 * Return: 0 when success, or error code when error.
 */

int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}
