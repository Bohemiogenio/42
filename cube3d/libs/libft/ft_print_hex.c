/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorente <mmorente@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:07:14 by mmorente          #+#    #+#             */
/*   Updated: 2026/09/16 12:31:30 by mmorente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex(unsigned long long num_hex)
{
	char				*base;
	unsigned long long	counter;

	base = "0123456789abcdef";
	counter = 0;
	if (num_hex >= 16)
	{
		counter += ft_print_hex(num_hex / 16);
		counter += ft_print_hex(num_hex % 16);
	}
	else
	{
		write(1, &base[num_hex], 1);
		counter++;
	}
	return (counter);
}
