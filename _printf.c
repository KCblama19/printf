#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - take variadic number of arguments.
 * @format: fix variable in printf variadic function.
 * Return: the printed chars.
 */
int _printf(const char *format, ...)
{
	int p_width, flag, p_precision, p_size;
	int p_buff_ind = 0;
	int k, printed = 0, printed_chars = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (k = 0; format && format[k] != '\0'; k++)
	{
		if (format[k] != '%')
		{
			buffer[p_buff_ind++] = format[k];
			if (p_buff_ind == BUFF_SIZE)
				print_buffer(buffer, &p_buff_ind);

			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &p_buff_ind);
			flag = get_flags(format, &k);
			p_width = get_width(format, &k, list);
			p_precision = get_precision(format, &k, list);
			p_size = get_size(format, &k);
			++k;
			printed = handle_print(format, &k, list, buffer,
				flag, p_width, p_precision, p_size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &p_buff_ind);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - Prints the buffer contents
 * @buffer: take array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
