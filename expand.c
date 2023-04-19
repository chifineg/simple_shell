#include "shell.h"

/**
 * expand_variables - funcion to expand variables
 * @data: points to program data struct
 *
 * Return: nothing, sets errno.
 */
void expand_variables(data_of_program *data)
{
	int x, y;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *holder;

	if (data->input_line == NULL)
		return;
	buffer_add(line, data->input_line);
	for (x = 0; line[x]; x++)
		if (line[x] == '#')
			line[x--] = '\0';
		else if (line[x] == '$' && line[x + 1] == '?')
		{
			line[x] = '\0';
			long_to_string(errno, expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + x + 2);
		}
		else if (line[x] == '$' && line[x + 1] == '$')
		{
			line[x] = '\0';
			long_to_string(getpid(), expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + x + 2);
		}
		else if (line[x] == '$' && (line[x + 1] == ' ' || line[x + 1] == '\0'))
			continue;
		else if (line[x] == '$')
		{
			for (y = 1; line[x + y] && line[x + y] != ' '; y++)
				expansion[y - 1] = line[x + y];
			holder = env_get_key(expansion, data);
			line[x] = '\0', expansion[0] = '\0';
			buffer_add(expansion, line + x + y);
			holder ? buffer_add(line, holder) : 1;
			buffer_add(line, expansion);
		}
	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * expand_alias - function to expand aliases
 * @data: points to program data struct
 *
 * Return: nothing, sets errno.
 */
void expand_alias(data_of_program *data)
{
	int x, y, expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *holder;

	if (data->input_line == NULL)
		return;

	buffer_add(line, data->input_line);

	for (x = 0; line[x]; x++)
	{
		for (y = 0; line[x + y] && line[x + y] != ' '; y++)
			expansion[y] = line[x + y];
		expansion[y] = '\0';

		holder = get_alias(data, expansion);
		if (holder)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + x + y);
			line[x] = '\0';
			buffer_add(line, holder);
			line[str_length(line)] = '\0';
			buffer_add(line, expansion);
			expanded = 1;
		}
		break;
	}
	if (expanded)
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * buffer_add - place string at end of buffer
 * @buffer: buffer to fill
 * @str_to_add: string to copy in the buffer
 * Return: nothing, sets errno.
 */
int buffer_add(char *buffer, char *str_to_add)
{
	int len, x;

	len = str_length(buffer);
	for (x = 0; str_to_add[x]; x++)
	{
		buffer[len + x] = str_to_add[x];
	}
	buffer[length + x] = '\0';
	return (len + x);
}
