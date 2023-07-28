#include "main.h"
/**
 * handle_print - Print the type of argument passed
 * @list: number of arguments to be printed.
 * @fmt: format of string in which to print the arguments.
 * @ind: take a integer
 * @buffer: handle printf
 * @flags: evaluates the number active flags
 * @width: check the width.
 * @precision: specification of precision
 * @size: specified size
 * Return: 1 otherwise 2;
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int j;
	int unknow_length = 0;
	int printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (j = 0; fmt_types[j].fmt != '\0'; j++)
		if (fmt[*ind] == fmt_types[j].fmt)
			return (fmt_types[j].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[j].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknow_length += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknow_length += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_length += write(1, &fmt[*ind], 1);
		return (unknow_length);
	}
	return (printed_chars);
}
