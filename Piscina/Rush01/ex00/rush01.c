/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:18:15 by raulsanc          #+#    #+#             */
/*   Updated: 2025/02/09 11:49:00 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "rush01.h"

int	main(int argc, char **argv)
{
	int	clues[SIZE * 4];
	int	grid[SIZE][SIZE];

	if (argc != 2 || !validate_input(argv[1], clues))
	{
		ft_putstr("Error\n");
		return (1);
	}
	ft_init_grid(grid);
	if (solve(grid, clues, 0, 0))
		print_grid(grid);
	else
		ft_putstr("Error\n");
	return (0);
}
