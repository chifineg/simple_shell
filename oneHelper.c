#include "shell.h"

/**
 * free_recurrent_data - in each loop the needed fields are freed
 * @data: the program data struct
 * Return: Nothing
 */
void free_recurrent_data(data_of_program *data)
{
	if (data->tokens)
		free_array_of_pointers(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}


void free_all_data(data_of_program *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	free_recurrent_data(data);
	free_array_of_pointers(data->env);
	free_array_of_pointers(data->alias_list);
}


void free_array_of_pointers(char **array)
{
	int k;

	if (array != NULL)
	{
		for (k = 0; array[k]; k++)
			free(array[k]);

		free(array);
		array = NULL;
	}
}
