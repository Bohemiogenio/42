/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:25:31 by raulsanc          #+#    #+#             */
/*   Updated: 2025/02/09 11:35:48 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "rush01.h"

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int	validate_input(char *str, int clues[SIZE *4])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && j < SIZE * 4)
	{
		if (str[i] >= '1' && str[i] <= '4')
			clues[j++] = str[i] - '0';
		else if (str[i] != ' ')
			return (0);
		i++;
	}
	return (j == SIZE * 4);
}

void	ft_init_grid(int grid[SIZE][SIZE])
{
	int	i;
	int	j;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
			grid[i][j++] = 0;
		i++;
	}
}
