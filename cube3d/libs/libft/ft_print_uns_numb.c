/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uns_numb.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorente <mmorente@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:02:49 by mmorente          #+#    #+#             */
/*   Updated: 2026/09/16 12:32:35 by mmorente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_uns_numb(unsigned int nb, int counter)
{
	if (nb < 10)
	{
		nb = nb + '0';
		counter += write (1, &nb, 1);
	}
	else
	{
		counter = ft_print_uns_numb((nb / 10), counter);
		nb = (nb % 10) + '0';
		write (1, &nb, 1);
		counter++;
	}
	return (counter);
}
