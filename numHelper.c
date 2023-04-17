#include "shell.h"

/**
 * long_to_string - string are converted from number.
 * @number: the number to be converted in a string.
 * @string: buffer use to save the number as string.
 * @base: the base to convert number
 *
 * Return: Nothing.
 */
void long_to_string(long number, char *string, int base)
{
	int index = 0, inNegative = 0;
	long cociente = number;
	char letters[] = {"0123456789abcdef"};

	if (cociente == 0)
		string[index++] = '0';

	if (string[0] == '-')
		inNegative = 1;

	while (cociente)
	{
		if (cociente < 0)
			string[index++] = letters[-(cociente % base)];
		else
			string[index++] = letters[cociente % base];
		cociente /= base;
	}
	if (inNegative)
		string[index++] = '-';

	string[index] = '\0';
	str_reverse(string);
}



int _atoi(char *s)
{
	int sign = 1;
	unsigned int number = 0;

	/*1- analisys sign*/
	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		if (*s == '+')
			sign *= +1;
		s++;
	}

	/*2 - extract the number */
	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * sign);
}

int count_characters(char *string, char *character)
{
	int j = 0, counter = 0;

	for (; string[j]; j++)
	{
		if (string[j] == character[0])
			counter++;
	}
	return (counter);
}
