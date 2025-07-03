/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Raulsanc <raulsanc@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:19:31 by Raulsanc          #+#    #+#             */
/*   Updated: 2025/07/01 17:19:32 by Raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_unsigned(unsigned int n)
{
	int		printed_chars;
	char	digit;

	printed_chars = 0;
	if (n > 9)
		printed_chars += ft_print_unsigned(n / 10);
	digit = (n % 10) + '0';
	write(1, &digit, 1);
	printed_chars++;
	return (printed_chars);
}
