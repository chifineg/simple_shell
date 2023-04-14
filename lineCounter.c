#include "shell.h"

/**
* _getline - gets a line from input.
* @data: program struct variable
*
* Return: count bytes.
*/
int _getline(data_of_program *data)
{
	char getBuff[BUFFER_SIZE] = {'\0'};
	static char *array_commands[10] = {NULL};
	static char array_operators[10] = {'\0'};
	ssize_t bytes_read, i = 0;

	if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
		(array_operators[0] == '|' && errno == 0))
	{
		/*free the memory allocated in the array if it exists */
		for (i = 0; array_commands[i]; i++)
		{
			free(array_commands[i]);
			array_commands[i] = NULL;
		}

		bytes_read = read(data->file_descriptor, &getBuff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		i = 0;
		do {
			array_commands[i] = str_duplicate(_strtok(i ? NULL : getBuff, "\n;"));
			i = check_logic_ops(array_commands, i, array_operators);
		} while (array_commands[i++]);
	}

	data->input_line = array_commands[0];
	for (i = 0; array_commands[i]; i++)
	{
		array_commands[i] = array_commands[i + 1];
		array_operators[i] = array_operators[i + 1];
	}

	return (str_length(data->input_line));
}


/**
* check_logic_ops - checks the && || operators and splits them
* @array_commands: command arrays.
* @i: array_commands index to test.
* @array_operators: logical operators array for each previous command
*
* Return: last command index in the array_commands.
*/
int check_logic_ops(char *array_commands[], int i, char array_operators[])
{
	char *holder = NULL;
	int x;

	for (x = 0; array_commands[i] != NULL  && array_commands[i][x]; x++)
	{
		if (array_commands[i][x] == '&' && array_commands[i][x + 1] == '&')
		{
			holder = array_commands[i];
			array_commands[i][x] = '\0';
			array_commands[i] = str_duplicate(array_commands[i]);
			array_commands[i + 1] = str_duplicate(holder + x + 2);
			i++;
			array_operators[i] = '&';
			free(holder);
			x = 0;
		}
		if (array_commands[i][x] == '|' && array_commands[i][x + 1] == '|')
		{
			holder = array_commands[i];
			array_commands[i][x] = '\0';
			array_commands[i] = str_duplicate(array_commands[i]);
			array_commands[i + 1] = str_duplicate(holder + x + 2);
			i++;
			array_operators[i] = '|';
			free(holder);
			x = 0;
		}
	}
	return (i);
}
