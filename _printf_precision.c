#include "main.h"

/**
 * get_precision - Calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: Precision.
 */
int get_precision(const char *format, int *i, va_list list)
{
	int precision = -1;	
	int next_char = *i + 1;

	if (format[next_char] != '.')
		return (precision);

	precision = 0;

	for (next_char += 1; format[next_char] != '\0'; next_char++)
	{
		if (is_digit(format[next_char]))
		{
			precision *= 10;
			precision += format[next_char] - '0';
		}
		else if (format[next_char] == '*')
		{
			next_char++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = next_char - 1;

	return (precision);
}
