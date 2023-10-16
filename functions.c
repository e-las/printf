#include "main.h"
#include <stdio.h>
#define define BUFF_SIZE 1024

/**A program that print char**/
/**Developer: e-las**/

/**
 * print_char - Program that Prints a char
 * @types: List a of arguments
 * @buffer: Reduce the number of write operations to output
 * @flags: control alignment and representation of the output
 * @width: specify the min width of output field
 * @precision: control the num decimal specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/**A program that print a string**/
/**
 * print_string - A program that prints a string
 * @types: List a of arguments
 * @buffer: Reduce the number of write operations to output
 * @flags: control alignment and representation of the output
 * @width: specify the min width of output field
 * @precision: control the num decimal specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, k;
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
			for (k = width - length; k > 0; k--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (k = width - length; k > 0; k--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}
	return (write(1, str, length));
}
/**A program that print a percent sign**/
/**
 * print_percent - A program that prints a percent sign
 * @types: List a of arguments
 * @buffer: Reduce the number of write operations to output
 * @flags: control alignment and representation of the output
 * @width: specify the min width of output field
 * @precision: control the num decimal specification
 * @size: Size specifier
 * Return: Number of chars printed
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

/**A program that print int**/
/**
 * print_int - A program that Print int
 * @types: List a of arguments
 * @buffer: buffer array to handle print
 * @flags: control alignment and representation of the output
 * @width: specify the min width of output field
 * @precision: control the num decimal specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
#define BUFF_SIZE 1024
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int k = BUFF_SIZE - 2;
	int is_negative = 0;
	long int w = va_arg(types, long int);
	unsigned long int numba;

	w = convert_size_number(w, size);
	if (w == 0)
		buffer[k--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	numba = (unsigned long int)w;
	if (w < 0)
	{
		numba = (unsigned long int)((-1) * w);
		is_negative = 1;
	}
	while (numba > 0)
	{
		buffer[k--] = (numba % 10) + '0';
		numba /= 10;
	}
	k++;
	return (write_number(is_negative, k, buffer, flags, width, precision, size));
}

/**A program that print binary**/
/**
 * print_binary - A program that prints an unsigned number
 * @types: List a of arguments
 * @buffer: Reduce the number of write operations to output
 * @flags: control alignment and representation of the output
 * @width: specify the min width of output field
 * @precision: control the num decimal specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int w, u, k, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	w = va_arg(types, unsigned int);
	u = 2147483648; /* (2 ^ 31) */
	a[0] = w / u;
	for (k = 1; k < 32; k++)
	{
		u /= 2;
		a[k] = (w / u) % 2;
	}
	for (k = 0, sum = 0, count = 0; k < 32; k++)
	{
		sum += a[k];
		if (sum || k == 31)
		{
			char z = '0' + a[k];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}

