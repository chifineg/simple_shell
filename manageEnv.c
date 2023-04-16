#include "shell.h"

/**
 * env_get_key - gives value of environment variable
 * @key: environment variable to test
 * @data: program data struct
 * Return: points to value of the variable, or NULL when doesn't exist
 */
char *env_get_key(char *key, data_of_program *data)
{
	int x, key_length = 0;

	if (key == NULL || data->env == NULL)
		return (NULL);

	key_length = str_length(key);

	for (x = 0; data->env[x]; x++)
	{
		if (str_compare(key, data->env[x], key_length) &&
		 data->env[x][key_length] == '=')
		{
			return (data->env[x] + key_length + 1);
		}
	}
	return (NULL);
}

/**
 * env_set_key - replaces value of the environment variable
 * or creates it if does not exist.
 * @key: variable name to set
 * @value: new value
 * @data: program data struct
 * Return: 1 when parameters are NULL, 2 when error, or 0 when success.
 */

int env_set_key(char *key, char *value, data_of_program *data)
{
	int x, key_length = 0, is_new_key = 1;

	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	key_length = str_length(key);

	for (x = 0; data->env[x]; x++)
	{
		if (str_compare(key, data->env[x], key_length) &&
		 data->env[x][key_length] == '=')
		{
			is_new_key = 0;
			free(data->env[x]);
			break;
		}
	}
	data->env[x] = str_concat(str_duplicate(key), "=");
	data->env[x] = str_concat(data->env[x], value);

	if (is_new_key)
	{
		data->env[x + 1] = NULL;
	}
	return (0);
}

/**
 * env_remove_key - remove key from the environment
 * @key: key to remove
 * @data: program data struct
 * Return: 1 when key was removed, 0 if key does not exist
 */
int env_remove_key(char *key, data_of_program *data)
{
	int x, key_length = 0;

	if (key == NULL || data->env == NULL)
		return (0);

	key_length = str_length(key);

	for (x = 0; data->env[x]; x++)
	{
		if (str_compare(key, data->env[x], key_length) &&
		 data->env[x][key_length] == '=')
		{
			free(data->env[x]);

			x++;
			for (; data->env[x]; x++)
			{
				data->env[x - 1] = data->env[x];
			}
			data->env[x - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * print_environ - function to print current environment
 * @data: program data struct
 * Return: Nothing
 */
void print_environ(data_of_program *data)
{
	int y;

	for (y = 0; data->env[y]; y++)
	{
		_print(data->env[y]);
		_print("\n");
	}
}
