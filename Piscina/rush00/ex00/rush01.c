/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimbroda <pimbroda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:39:07 by pimbroda          #+#    #+#             */
/*   Updated: 2025/02/02 13:50:36 by pimbroda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c);

void	imprimirlinea(int ancho, char primero, char medio, char ultimo)
{
	int	i;

	if (ancho > 0)
	{
		ft_putchar(primero);
	}
	i = 1;
	while (i < ancho - 1)
	{
		ft_putchar(medio);
		i++;
	}
	if (ancho > 1)
	{
		ft_putchar(ultimo);
	}
	ft_putchar('\n');
}

void	rush(int x, int y)
{
	int	i;

	if (x <= 0 || y <= 0)
	{
		return ;
	}
	imprimirlinea(x, '/', '*', '\\');
	i = 1;
	while (i < y - 1)
	{
		imprimirlinea(x, '*', ' ', '*');
		i++;
	}
	if (y > 1)
	{
		imprimirlinea(x, '\\', '*', '/');
	}
}
