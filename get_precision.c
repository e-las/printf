#include "main.h"

/**
 * get_precision - Calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @k: List of arguments to be printed.
 * @arg_list: list of arguments.
 *
 * Return: Precision.
 */
int get_precision(const char *format, int *k, va_list arg_list)
{
	int curr_k = *k + 1;
	int precision = -1;

	if (format[curr_k] != '.')
		return (precision);
	precision = 0;
	for (curr_k += 1; format[curr_k] != '\0'; curr_k++)
	{
		if (is_digit(format[curr_k]))
		{
			precision *= 10;
			precision += format[curr_k] - '0';
		}
		else if (format[curr_k] == '*')
		{
			curr_k++;
			precision = va_arg(arg_list, int);
			break;
		}
		else
			break;
	}
	*k = curr_k - 1;
	return (precision);
}
