#include "shell.h"

/**
 * print_alias - addition, removal and displaying of aliases
 * @data: program data struct 
 * @alias: alias names to be displayed
 * Return: 0 when success, other number when argumens is declared
 */
int print_alias(data_of_program *data, char *alias)
{
	int x, y, alias_length;
	char getBuffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_length = str_length(alias);
		for (x = 0; data->alias_list[x]; x++)
		{
			if (!alias || (str_compare(data->alias_list[x], alias, alias_length)
				&&	data->alias_list[x][alias_length] == '='))
			{
				for (y = 0; data->alias_list[x][y]; y++)
				{
					getBuffer[y] = data->alias_list[x][y];
					if (data->alias_list[x][y] == '=')
						break;
				}
				getBuffer[y + 1] = '\0';
				buffer_add(getBuffer, "'");
				buffer_add(getBuffer, data->alias_list[x] + y + 1);
				buffer_add(getBuffer, "'\n");
				_print(getBuffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - addition, removal and showing aliases
 * @data: program data struct 
 * @name: alias requested name.
 * Return: 0 when success, or other number when argument
 */
char *get_alias(data_of_program *data, char *name)
{
	int x, alias_length;

	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_length = str_length(name);

	for (x = 0; data->alias_list[x]; x++)
		if (str_compare(name, data->alias_list[x], alias_length) &&
			data->alias_list[x][alias_length] == '=')
		{
			return (data->alias_list[x] + alias_length + 1);
		}
	}
	return (NULL);

}

/**
 * set_alias - addition and overriding alias
 * @alias_string: setting alias in the form (name='value')
 * @data: program's data struct
 * Return: 0 when success, other number when argument is declared
 */
int set_alias(char *alias_string, data_of_program *data)
{
	int x, y;
	char getBuffer[250] = {'0'}, *holder = NULL;

	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);
	for (x = 0; alias_string[x]; x++)
		if (alias_string[x] != '=')
			getBuffer[x] = alias_string[x];
		else
		{
			holder = get_alias(data, alias_string + x + 1);
			break;
		}

	for (y = 0; data->alias_list[y]; y++)
		if (str_compare(getBuffer, data->alias_list[y], x) &&
			data->alias_list[y][x] == '=')
		{
			free(data->alias_list[y]);
			break;
		}

	if (holder)
	{
		buffer_add(getBuffer, "=");
		buffer_add(getBuffer, holder);
		data->alias_list[y] = str_duplicate(getBuffer);
	}
	else
		data->alias_list[y] = str_duplicate(alias_string);
	return (0);
}
