#include "main.h"

/********|| PRINT A STRING IN ROT13 ||**********/
/**
 * print_rot13string - write a string in rot13 to std-O
 * @types: number of arguments
 * @buffer: array to handle printf in the buffer
 * @flags:  indicate active flags
 * @width: take width
 * @precision: specified a precision
 * @size: specified size
 * Return: characters to be printed
 */
int print_rot13string(va_list types, char buffer[],
        int flags, int width, int precision, int size)
{
        char chr;
        char *str;
        unsigned int i, j;
        int count = 0;
        char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

        str = va_arg(types, char *);
        UNUSED(buffer);
        UNUSED(flags);
        UNUSED(width);
        UNUSED(precision);
        UNUSED(size);

        if (str == NULL)
                str = "(AHYY)";
        for (i = 0; str[i]; i++)
        {
                for (j = 0; in[j]; j++)
                {
                        if (in[j] == str[i])
                        {
                                chr = out[j];
                                write(1, &chr, 1);
                                count++;
                                break;
                        }
                }
                if (!in[j])
                {
                        chr = str[i];
                        write(1, &chr, 1);
                        count++;
                }
        }
        return (count);
}


/*********|| PRINT A POINTER ||**********/
/**
 * print_pointer - write the value of a pointer variable to std-O
 * @types: number of arguments
 * @buffer: array to handle printf in the buffer
 * @flags:  indicate active flags
 * @width: take a width
 * @precision: specified precision
 * @size: specified size
 * Return: character to be printed
 */
int print_pointer(va_list types, char buffer[],
        int flags, int width, int precision, int size)
{
        char extra_c = 0;
	char padding = ' ';
        int ind = BUFF_SIZE - 2, length = 2, padd_start = 1;
        unsigned long num_addrs;
        char map_to[] = "0123456789abcdef";
        void *addrs = va_arg(types, void *);

        UNUSED(width);
        UNUSED(size);

        if (addrs == NULL)
                return (write(1, "(nil)", 5));

        buffer[BUFF_SIZE - 1] = '\0';
        UNUSED(precision);

        num_addrs = (unsigned long)addrs;

        while (num_addrs > 0)
        {
                buffer[ind--] = map_to[num_addrs % 16];
                num_addrs /= 16;
                length++;
        }

        if ((flags & F_ZERO) && !(flags & F_MINUS))
                padding = '0';
        if (flags & F_PLUS)
                extra_c = '+', length++;
        else if (flags & F_SPACE)
                extra_c = ' ', length++;

        ind++;

        return (write_pointer(buffer, ind, length,
                width, flags, padding, extra_c, padd_start));
}

/*************|| PRINT A NON PRINTABLE ||***********/
/**
 * print_non_printable - write ASCII in hexa for non printable chars
 * @types: number of arguments
 * @buffer: array to handle printf in the buffer
 * @flags:  indicate active flags
 * @width: take width
 * @precision: specified precision
 * @size: specified size
 * Return: characters to be printed
 */
int print_non_printable(va_list types, char buffer[],
        int flags, int width, int precision, int size)
{
        int num = 0; 
	int offset = 0;
        char *str = va_arg(types, char *);

        UNUSED(flags);
        UNUSED(width);
        UNUSED(precision);
        UNUSED(size);

        if (str == NULL)
                return (write(1, "(null)", 6));

        while (str[num] != '\0')
        {
                if (is_printable(str[num]))
                        buffer[num + offset] = str[num];
                else
                        offset += append_hexa_code(str[num], buffer, num + offset);

                num++;
        }

        buffer[num + offset] = '\0';

        return (write(1, buffer, num + offset));
}

/*************|| PRINT REVERSE ||****************/
/**
 * print_reverse - write a reverse string.
 * @types: Number of arguments
 * @buffer: array to handle printf in the bufer
 * @flags: indicate active flags
 * @width: take width
 * @precision: specified precision
 * @size: specified size
 * Return: characters to be printed
 */

int print_reverse(va_list types, char buffer[],
        int flags, int width, int precision, int size)
{
        char *str;
	int counts = 0;
	int num;

        UNUSED(buffer);
        UNUSED(flags);
        UNUSED(width);
        UNUSED(size);

        str = va_arg(types, char *);

        if (str == NULL)
        {
                UNUSED(precision);

                str = ")Null(";
        }
        for (num = 0; str[num]; num++)
                ;

        for (num = num - 1; num >= 0; num--)
        {
                char a = str[num];

                write(1, &a, 1);
                counts++;
        }
        return (counts);
}
