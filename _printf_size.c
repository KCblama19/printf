#include "main.h"

/**
 * get_size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 *
 * Return: Precision.
 */
int get_size(const char *format, int *i)
{
	int next_i = *i + 1;
	int size = 0;

	if (format[next_i] == 'l')
		size = SI_LONG;
	else if (format[next_i] == 'h')
		size = SI_SHORT;

	if (size == 0)
		*i = next_i - 1;
	else
		*i = next_i;

	return (size);
}

