/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_may.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorente <mmorente@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:19:14 by mmorente          #+#    #+#             */
/*   Updated: 2026/09/16 12:31:49 by mmorente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex_may(unsigned long long num_hex)
{
	char				*base;
	unsigned long long	counter;

	counter = 0;
	base = "0123456789ABCDEF";
	if (num_hex > 15)
	{
		counter += ft_print_hex_may(num_hex / 16);
		counter += ft_print_hex_may(num_hex % 16);
	}
	else
	{
		write(1, &base[num_hex], 1);
		counter++;
	}
	return (counter);
}
