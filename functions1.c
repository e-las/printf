#include "main.h"
#include <stdio.h>
#define BUFF_SIZE 1024

/**A program that print unsigned number**/
/**Developer: e-las**/

/**
 * print_unsigned - A program that prints an unsigned number
 * @types: List a of arguments
 * @buffer: Reduce the number of write operations to output
 * @flags: control alignment and representation of the output
 * @width: specify the min width of output field
 * @precision: control the num decimal specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int numba = va_arg(types, unsigned long int);

	numba = convert_size_unsgnd(numba, size);

	if (numba == 0)
		buffer[i--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	while (numba > 0)
	{
		buffer[i--] = (numba % 10) + '0';
		numba /= 10;
	}
	i++;
	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**A program that print unsigned number in OCTAL**/
/**
 * print_octal - Prints an unsigned number in octal notation
 * @types: List a of arguments
 * @buffer: Reduce the number of write operations to output
 * @flags: control alignment and representation of the output
 * @width: specify the min width of output field
 * @precision: control the num decimal specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int numba = va_arg(types, unsigned long int);
	unsigned long int init_numba = numba;

	UNUSED(width);
	numba = convert_size_unsgnd(numba, size);
	if (numba == 0)
		buffer[i--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	while (numba > 0)
	{
		buffer[i--] = (numba % 8) + '0';
		numba /= 8;
	}
	if (flags & F_HASH && init_numba != 0)
		buffer[i--] = '0';
	i++;
	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**A program that print unsigned number in HEX**/
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @types: List a of arguments
 * @buffer: Reduce the number of write operations to output
 * @flags: control alignment and representation of the output
 * @width: specify the min width of output field
 * @precision: control the num decimal specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
	flags, 'x', width, precision, size));
}

/**A program that unsigned number in upper HEX**/
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @types: List a of arguments
 * @buffer: Reduce the number of write operations to output
 * @flags: control alignment and representation of the output
 * @width: specify the min width of output field
 * @precision: control the num decimal specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
	flags, 'X', width, precision, size));
}

/**A program that print HEX NUM in lower OR Upper**/
/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @types: list of arguments
 * @map_to: Array of values to map the number
 * @buffer: Reduce the number of write operations to output
 * @flags: control alignment and representation of the output
 * @flag_ch: calculates the active flags
 * @width: specify the min width of output field
 * @precision: control the num decimal specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int numba = va_arg(types, unsigned long int);
	unsigned long int init_numba = numba;

	UNUSED(width);
	numba = convert_size_unsgnd(numba, size);
	if (numba == 0)
		buffer[i--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	while (numba > 0)
	{
		buffer[i--] = map_to[numba % 16];
		numba /= 16;
	}
	if (flags & F_HASH && init_numba != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}
	i++;
	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
