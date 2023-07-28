#include "main.h"

/*************|| PRINT UNSIGNED NUMBER IN HEXADECIMAL ||************/
/**
 * print_hexadecimal - write an unsigned number in hexadecimal notation
 * @types: number of arguments
 * @buffer: handle printf in the buffer
 * @flags:  indicates active flags
 * @width: take width
 * @precision: specified precision
 * @size: specified size
 * Return: unsigned number in hexadecimal
 */
int print_hexadecimal(va_list types, char buffer[],
        int flags, int width, int precision, int size)
{
        return (print_hexa(types, "0123456789abcdef", buffer,
                flags, 'x', width, precision, size));
}

/*******|| PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL ||********/

/**
 * print_hexa_upper - write an unsigned number in upper hexadecimal 
 * @types: number of arguments
 * @buffer: array to handle printf in the buffer
 * @flags:  indicate active flags
 * @width: take width
 * @precision: specified precision
 * @size: specified size
 * Return: number of upper hexadecimal
 */
int print_hexa_upper(va_list types, char buffer[],
        int flags, int width, int precision, int size)
{
        return (print_hexa(types, "0123456789ABCDEF", buffer,
                flags, 'X', width, precision, size));
}

/********|| PRINT HEXX NUM IN LOWER OR UPPER ||********/
/**
 * print_hexa - write a hexadecimal number in lower or upper
 * @types: number of arguments
 * @map_to: map a arrays of value
 * @buffer: array to handle printf in the buffer
 * @flags:  indicate active flags
 * @flag_ch: check for active flags
 * @width: take a width
 * @precision: specified precision
 * @size: specified size
 * Return: characters to be printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
        int flags, char flag_ch, int width, int precision, int size)
{
        int i = BUFF_SIZE - 2;
        unsigned long int num = va_arg(types, unsigned long int);
        unsigned long int init_num = num;

        UNUSED(width);

        num = convert_size_unsgnd(num, size);

        if (num == 0)
                buffer[i--] = '0';

        buffer[BUFF_SIZE - 1] = '\0';

        while (num > 0)
        {
                buffer[i--] = map_to[num % 16];
                num /= 16;
        }

        if (flags & F_HASH && init_num != 0)
        {
                buffer[i--] = flag_ch;
                buffer[i--] = '0';
        }

        i++;

        return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}


/******|| PRINT UNSIGNED NUMBER ||*******/
/**
 * print_unsigned - write an unsigned number to std-O
 * @types: number of arguments
 * @buffer: array to handle printf in the buffer
 * @flags: indicate active flags
 * @width: take width
 * @precision: specified precision
 * @size: specified size
 * Return: characters to be printed
 */
int print_unsigned(va_list types, char buffer[],
        int flags, int width, int precision, int size)
{
        int i = BUFF_SIZE - 2;
        unsigned long int num = va_arg(types, unsigned long int);

        num = convert_size_unsgnd(num, size);

        if (num == 0)
                buffer[i--] = '0';

        buffer[BUFF_SIZE - 1] = '\0';

        while (num > 0)
        {
                buffer[i--] = (num % 10) + '0';
                num /= 10;
        }

        i++;

        return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/******|| PRINT UNSIGNED NUMBER IN OCTAL ||*******/
/**
 * print_octal - write an unsigned number in octal notation to std-O
 * @types: Number of arguments
 * @buffer: array to handle printf in the buffer
 * @flags: indicate active flags
 * @width: take width
 * @precision: specified a precision
 * @size: specified size
 * Return: character to be printed
 */
int print_octal(va_list types, char buffer[],
        int flags, int width, int precision, int size)
{

        int i = BUFF_SIZE - 2;
        unsigned long int num = va_arg(types, unsigned long int);
        unsigned long int init_num = num;

        UNUSED(width);

        num = convert_size_unsgnd(num, size);

        if (num == 0)
                buffer[i--] = '0';

        buffer[BUFF_SIZE - 1] = '\0';

        while (num > 0)
        {
                buffer[i--] = (num % 8) + '0';
                num /= 8;
        }

        if (flags & F_HASH && init_num != 0)
                buffer[i--] = '0';

        i++;

        return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
