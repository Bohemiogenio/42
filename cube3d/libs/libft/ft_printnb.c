/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorente <mmorente@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:52:41 by mmorente          #+#    #+#             */
/*   Updated: 2026/09/16 12:33:08 by mmorente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printnb(int n, int counter)
{
	if (n == INT_MIN)
	{
		write(1, "-2147483648", 11);
		counter = 11;
		return (counter);
	}
	if (n < 0 && n != INT_MIN)
	{
		write(1, "-", 1);
		counter++;
		n = -n;
	}
	if (n < 10)
	{
		n = n + '0';
		write(1, &n, 1);
		counter++;
	}
	else
	{
		counter = ft_printnb((n / 10), counter);
		n = (n % 10) + '0';
		counter += write(1, &n, 1);
	}
	return (counter);
}
