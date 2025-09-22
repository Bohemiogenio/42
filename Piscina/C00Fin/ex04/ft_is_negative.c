/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_negative.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:48:42 by raulsanc          #+#    #+#             */
/*   Updated: 2025/01/31 14:33:05 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

void	ft_is_negative(int n)
{
	char	resultado;

	if (n < 0)
	{
		resultado = 'N';
	}
	else
	{
		resultado = 'P';
	}
	write(1, &resultado, 1);
}
