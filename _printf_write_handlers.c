#include "main.h"

/*************|| WRITE NUMBER ||***************/
/**
 * write_number - show a string
 * @is_negative: number of arguments in negative
 * @ind: character types.
 * @buffer: handle printf
 * @flags: evaluate the active flags
 * @width: check the width.
 * @precision: specifier of precision
 * @size: specifier of size
 *
 * Return: amount of characters printed.
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padding = ' ';
	char extra_char = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';
	if (is_negative)
		extra_char = '-';
	else if (flags & F_PLUS)
		extra_char = '+';
	else if (flags & F_SPACE)
		extra_char = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		length, padd, extra_char));
}

/**
 * write_num - used the buffer to write a number
 * @ind: start of the number in the buffer
 * @buffer: hold the buffer
 * @flags: hold the flags
 * @width: hold the width
 * @prec: specifier of precision
 * @length: lenght of the number
 * @padd: char padding
 * @extra_c: extra character
 *
 * Return: Number of printed chars.
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int i; 
	int padding_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); 
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' ';
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padding_start] = extra_c;
			return (write(1, &buffer[padding_start], i - padding_start) +
				write(1, &buffer[ind], length - (1 - padding_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - print an unsigned number
 * @is_negative: indicate a negative number
 * @ind: start of the number in the buffer
 * @buffer: array of characters
 * @flags: specifier of a flags
 * @width: specifier of a width
 * @precision: specifier of a precision
 * @size: specifier of a size
 *
 * Return: Number of characters written.
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	
	char padding = ' ';
	int length = BUFF_SIZE - ind - 1, i = 0;

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); 

	if (precision > 0 && precision < length)
		padding = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padding;

		buffer[i] = '\0';

		if (flags & F_MINUS) 
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
		}
		else 
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - print the memory address
 * @buffer: array of character in the buffer
 * @ind: starting of number in the buffer
 * @length: print the length 
 * @width: specified a width
 * @flags: specified a flags
 * @padd: padding of the characters
 * @extra_c: extra char representation of the characters
 * @padd_start: starting point of the characters
 *
 * Return: amount of written characters.
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int num;

	if (width > length)
	{
		for (num = 3; num < width - length + 3; num++)
			buffer[num] = padd;
		buffer[num] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], num - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], num - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], num - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}


/***********||  WRITE HANDLE  ||***************/
/**
 * handle_write_char - write a string 
 * @c: take a character types
 * @buffer:  indicate a array to handle print
 * @flags:  evaluate the active flags.
 * @width: take the width.
 * @precision: specifier of precision
 * @size: specifier of size
 *
 * Return: amount of characters.
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and paddind at buffer's right */
	int i = 0;
	char padding = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padding = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padding;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

