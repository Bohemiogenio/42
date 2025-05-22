/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:35:36 by jsalado-          #+#    #+#             */
/*   Updated: 2025/01/23 15:05:13 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_fprintf(va_list args, const char f)
{
	int	len;

	len = 0;
	if (f == 'c')
		len += ft_putchar(va_arg(args, int));
	else if (f == 's')
		len += ft_printstr(va_arg(args, char *));
	else if (f == 'p')
		len += ft_print_ptr(va_arg(args, unsigned long long));
	else if (f == 'd' || f == 'i')
		len += ft_printnbr(va_arg(args, int));
	else if (f == 'u')
		len += ft_print_unsigned(va_arg(args, unsigned int));
	else if (f == 'x' || f == 'X')
		len += ft_print_hex(va_arg(args, unsigned int), f);
	else if (f == '%')
		len += ft_printpercent();
	return (len);
}

int	ft_printf(char const *s, ...)
{
	va_list	args;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			len += ft_fprintf(args, s[i + 1]);
			i++;
		}
		else
			len += ft_putchar(s[i]);
		i++;
	}
	va_end(args);
	return (len);
}
