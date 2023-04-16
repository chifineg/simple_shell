#include "shell.h"

/**
 * builtin_exit - closes the program
 * @data: program data struct
 * Return: 0 when success, other number when arguments is declared
 */
int builtin_exit(data_of_program *data)
{
	int x;

	if (data->tokens[1] != NULL)
	{
		for (x = 0; data->tokens[1][x]; x++)
			if ((data->tokens[1][x] < '0' || data->tokens[1][x] > '9')
				&& data->tokens[1][x] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tokens[1]);
	}
	free_all_data(data);
	exit(errno);
}

/**
 * builtin_cd - change current directory
 * @data: program data struct
 * Return: 0 when success, other number when argument is declared
 */
int builtin_cd(data_of_program *data)
{
	char *dir_home = env_get_key("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (data->tokens[1])
	{
		if (str_compare(data->tokens[1], "-", 0))
		{
			dir_old = env_get_key("OLDPWD", data);
			if (dir_old)
				error_code = set_work_directory(data, dir_old);
			_print(env_get_key("PWD", data));
			_print("\n");

			return (error_code);
		}
		else
		{
			return (set_work_directory(data, data->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, 128);

		return (set_work_directory(data, dir_home));
	}
	return (0);
}

/**
 * set_work_directory - set working directory
 * @data: program data struct
 * @new_dir: directory to set as working directory
 * Return: 0 when success, other number when argument is declared
 */
int set_work_directory(data_of_program *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!str_compare(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		env_set_key("PWD", new_dir, data);
	}
	env_set_key("OLDPWD", old_dir, data);
	return (0);
}

/**
 * builtin_help - gives environment where the shell runs
 * @data: program data struct
 * Return: 0 when success, other number when argument is declared
 */
int builtin_help(data_of_program *data)
{
	int x, len = 0;
	char *stud[6] = {NULL};

	stud[0] = HELP_MSG;

	if (data->tokens[1] == NULL)
	{
		_print(stud[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	stud[1] = HELP_EXIT_MSG;
	stud[2] = HELP_ENV_MSG;
	stud[3] = HELP_SETENV_MSG;
	stud[4] = HELP_UNSETENV_MSG;
	stud[5] = HELP_CD_MSG;

	for (x = 0; stud[x]; x++)
	{
		len = str_length(data->tokens[1]);
		if (str_compare(data->tokens[1], stud[x], len))
		{
			_print(stud[x] + len + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}

/**
 * builtin_alias - addition, removal and showing aliases
 * @data: program data struct
 * Return: 0 when success, other number when argument is declared
 */
int builtin_alias(data_of_program *data)
{
	int x = 0;

	if (data->tokens[1] == NULL)
		return (print_alias(data, NULL));

	while (data->tokens[++x])
	{
		if (count_characters(data->tokens[x], "="))
			set_alias(data->tokens[x], data);
		else
			print_alias(data, data->tokens[x]);
	}

	return (0);
}
