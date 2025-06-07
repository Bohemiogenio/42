#include "ft_printf.h"

int	ft_format(va_list args, const char format)
{
	int	print_length;

	print_length = 0;
	if (format == 'c')
		print_length += ft_printchar(va_arg(args, int));
	else if (format == 's')
		print_length += ft_printstr(va_arg(args, char *));
	else if (format == 'p')
		print_length += ft_printptr(va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		print_length += ft_printnbr(va_arg(args, int));
	else if (format == 'u')
		print_length += ft_print_unsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		print_length += ft_printhex(va_arg(args, unsigned int), format);
	else if (format == '%')
		print_length += write(1, "%", 1);
	return (print_length);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		print_length;

	i = 0;
	print_length = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			print_length += ft_format(args, str[i]);
		}
		else
		{
			write(1, &str[i], 1);
			print_length++;
		}
		i++;
	}
	va_end(args);
	return (print_length);
}

