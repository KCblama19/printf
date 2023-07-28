#include "main.h"

/************************* PRINT INT *************************/

/**
 * print_int - print an integer
 * @types: types of integer(unsigned, signed, short)
 * @buffer: handle printf in the buffer
 * @flags: indicate active flags
 * @width: take a width.
 * @precision: specified a precision 
 * @size: specified a size
 * Return: print number of characters
 */
int print_int(va_list types, char buffer[],
             int flags, int width, int precision, int size)
{
        int j = BUFF_SIZE - 2;
        int is_negative = 0;
        long int n = va_arg(types, long int);
        unsigned long int num;

        n = convert_size_number(n, size);

        if (n == 0)
                buffer[j--] = '0';

        buffer[BUFF_SIZE - 1] = '\0';
        num = (unsigned long int)n;

        if (n < 0)
        {
                num = (unsigned long int)((-1) * n);
                is_negative = 1;
        }

        while (num > 0)
        {
                buffer[j--] = (num % 10) + '0';
                num /= 10;
        }

        j++;

        return (write_number(is_negative, j, buffer, flags, width, precision, size));
}

/************************* PRINT CHAR *************************/

/**
 * print_char - write a character to the std-O
 * @types: list of characters
 * @buffer: handle printf in the buffer
 * @flags: indicate active flag
 * @width: take a width
 * @precision: specified a precision
 * @size: specified a size
 * Return: a character
 */
int print_char(va_list types, char buffer[],
              int flags, int width, int precision, int size)
{
        char c = va_arg(types, int);

        return (handle_write_char(c, buffer, flags, width, precision, size));
}

/************************* PRINT A STRING *************************/
/**
 * print_string - write a string to std-O
 * @types: number of strings
 * @buffer: used to handle printf in the buffer
 * @flags: indicate active flags
 * @width: take a width.
 * @precision: specified a precision
 * @size: specified a size
 * Return: the number characters to print
 */
int print_string(va_list types, char buffer[],
                 int flags, int width, int precision, int size)
{
        int length = 0, j;
        char *str = va_arg(types, char *);

        UNUSED(buffer);
        UNUSED(flags);
        UNUSED(width);
        UNUSED(precision);
        UNUSED(size);
        if (str == NULL)
        {
                str = "(null)";
                if (precision >= 6)
                        str = "      ";
        }

        while (str[length] != '\0')
                length++;

        if (precision >= 0 && precision < length)
                length = precision;

        if (width > length)
        {
                if (flags & F_MINUS)
                {
                        write(1, &str[0], length);
                        for (j = width - length; j > 0; j--)
                                write(1, " ", 1);
                        return (width);
                }
                else
                {
                        for (j = width - length; j > 0; j--)
                                write(1, " ", 1);
                        write(1, &str[0], length);
                        return (width);
                }
        }

        return (write(1, str, length));
}

/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - write a percent sign to std-O
 * @types: number of argument
 * @buffer: handle printf in the buffer
 * @flags: indicate active flags
 * @width: take a width.
 * @precision: specified a precision
 * @size: specified a size
 * Return: the numbers of characters
 */
int print_percent(va_list types, char buffer[],
                  int flags, int width, int precision, int size)
{
        UNUSED(types);
        UNUSED(buffer);
        UNUSED(flags);
        UNUSED(width);
        UNUSED(precision);
        UNUSED(size);
        return (write(1, "%%", 1));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - write an unsigned number to std-O
 * @types: number of arguements
 * @buffer: handle printf in the buffer
 * @flags: indicate active flags
 * @width: take a width.
 * @precision: specified a precision
 * @size: specified a size
 * Return: a unsigned number
 */
int print_binary(va_list types, char buffer[],
                 int flags, int width, int precision, int size)
{
        unsigned int n, m, j, sum;
        unsigned int a[32];
        int count;

        UNUSED(buffer);
        UNUSED(flags);
        UNUSED(width);
        UNUSED(precision);
        UNUSED(size);

        n = va_arg(types, unsigned int);
        m = 2147483648; /* (2 ^ 31) */
        a[0] = n / m;
        for (j = 1; j < 32; j++)
        {
                m /= 2;
                a[j] = (n / m) % 2;
        }
        for (j = 0, sum = 0, count = 0; j < 32; j++)
        {
                sum += a[j];
                if (sum || j == 31)
                {
                        char z = '0' + a[j];

                        write(1, &z, 1);
                        count++;
                }
        }
        return (count);
}
