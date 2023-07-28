#include "main.h"

/**
 * get_width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: width.
 */
int get_width(const char *format, int *i, va_list list)
{
	int width = 0;
	int next_i;


	for (next_i = *i + 1; format[next_i] != '\0'; next_i++)
	{
		if (is_digit(format[next_i]))
		{
			width *= 10;
			width += format[next_i] - '0';
		}
		else if (format[next_i] == '*')
		{
			next_i++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = next_i - 1;

	return (width);
}

