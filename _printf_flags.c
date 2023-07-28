#include "main.h"

/**
 * get_flags - evaluate the active flags
 * @format: format to print the argument
 * @i: hold a parameter.
 * Return: the flags
 */
int get_flags(const char *format, int *i)
{
	int j, next_i;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (next_i = *i + 1; format[next_i] != '\0'; next_i++)
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
			if (format[next_i] == FLAGS_CH[j])
			{
				flags |= FLAGS_ARR[j];
				break;
			}

		if (FLAGS_CH[j] == 0)
			break;
	}

	*i = next_i - 1;

	return (flags);
}
