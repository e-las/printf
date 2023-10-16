#include "main.h"

/**
 * get_width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @k: List of arguments to be printed.
 * @arg_list: list of arguments.
 *
 * Return: width.
 */
int get_width(const char *format, int *k, va_list arg_list)
{
	int curr_k;
	int width = 0;

	for (curr_k = *k + 1; format[curr_k] != '\0'; curr_k++)
	{
		if (is_digit(format[curr_k]))
		{
			width *= 10;
			width += format[curr_k] - '0';
		}
		else if (format[curr_k] == '*')
		{
			curr_k++;
			width = va_arg(arg_list, int);
			break;
		}
		else
			break;
	}
	*k = curr_k - 1;
	return (width);
}

