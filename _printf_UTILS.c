#include "main.h"

/**
 * convert_size_number - move a number to the specified size
 * @num: show the number to be casted
 * @size: indicate the number to be casted
 *
 * Return: value casted
 */
long int convert_size_number(long int num, int size)
{
	if (size == SI_LONG)
		return (num);
	else if (size == SI_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - move a number to a specified size
 * @num: show the number to be casted
 * @size: the type to be casted
 *
 * Return: value of num casted
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == SI_LONG)
		return (num);
	else if (size == SI_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}

/**
 * is_printable - check if a char is printable
 * @c: check for a char
 *
 * Return: 1 if "c" is printable, otherwise 0
 */
int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - append asci to hexadecimal code
 * @buffer: take a array of char
 * @i: show the indec to append start appending from
 * @ascii_code: asci code.
 * Return: Always (3)
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";
	
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - verified the digit of a char
 * @c: evaluate a char
 *
 * Return: 1 if "c" is a digit, otherwise 0
 */
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}
