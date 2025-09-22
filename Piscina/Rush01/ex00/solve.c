/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:58:36 by raulsanc          #+#    #+#             */
/*   Updated: 2025/02/09 12:02:14 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "rush01.h"

int	is_valid(int grid[SIZE][SIZE], int row, int col, int num)
{
	int	i;

	i = 0;
	while (i < SIZE)
	{
		if (grid[row][i] == num || grid[i][col] == num)
			return (0);
		i++;
	}
	return (1);
}

int	solve(int grid[SIZE][SIZE], int clues[SIZE *4], int row, int col)
{
	int	num;
	int	next_row;
	int	next_col;

	if (row == SIZE)
		return (check_visibility(grid, clues));
	if (col == SIZE - 1)
	{
		next_row = row + 1;
		next_col = 0;
	}
	else
	{
		next_row = row;
		next_col = col + 1;
	}
	num = 1;
	while (num <= SIZE)
	{
		if (is_valid(grid, row, col, num))
		{
			grid[row][col] = num;
			if (solve(grid, clues, next_row, next_col))
				return (1);
			grid[row][col] = 0;
		}
		num++;
	}
	return (0);
}
