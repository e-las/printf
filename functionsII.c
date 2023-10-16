#include "main.h"

/**A program that print a pointer**/
/**Developer: e-las**/
/**
 * print_pointer - A program that Prints the value of a pointer variable
 * @types: List a of arguments
 * @buffer: Reduce the number of write operations to output
 * @flags: control alignment and representation of the output
 * @width: specify the min width of output field
 * @precision: control the num decimal specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
#define BUFF_SIZE 1024
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
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
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;
	ind++;
	/*return (write(1, &buffer[k], BUFF_SIZE - k - 1));*/
	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}

/**A program that print Non printable**/
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: List a of arguments
 * @buffer: Reduce the number of write operations to output
 * @flags: control alignment and representation of the output
 * @width: specify the min width of output field
 * @precision: control the num decimal specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int k = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
		return (write(1, "(null)", 6));
	while (str[k] != '\0')
	{
		if (is_printable(str[k]))
			buffer[k + offset] = str[k];
		else
			offset += append_hexa_code(str[k], buffer, k + offset);
		k++;
	}
	buffer[k + offset] = '\0';
	return (write(1, buffer, k + offset));
}

/** A program print reverse**/
/**
 * print_reverse - A program prints reverse string.
 * @types: List a of arguments
 * @buffer: Reduce the number of write operations to output
 * @flags: control alignment and representation of the output
 * @width: specify the min width of output field
 * @precision: control the num decimal specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int k, count = 0;

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
	for (k = 0; str[k]; k++)
		;
	for (k = k - 1; k >= 0; k--)
	{
		char z = str[k];

		write(1, &z, 1);

		count++;
	}
												return (count);
}

/**A program that print a string in ROT13**/
/**
 * print_rot13string - Print a string in rot13.
 * @types: List a of arguments
 * @buffer: Reduce the number of write operations to output
 * @flags: control alignment and representation of the output
 * @width: specify the min width of output field
 * @precision: control the num decimal specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char e;
	char *str;
	unsigned int k, y;
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
	for (k = 0; str[k]; k++)
	{
		for (y = 0; in[y]; y++)
		{
			if (in[y] == str[k])
			{
				e = out[y];
				write(1, &e, 1);
				count++;
				break;
			}
		}
		if (!in[y])
		{
			e = str[k];
			write(1, &e, 1);
			count++;
		}
	}
	return (count);
}
