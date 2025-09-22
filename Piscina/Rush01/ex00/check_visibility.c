/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_visibility.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:50:47 by raulsanc          #+#    #+#             */
/*   Updated: 2025/02/09 11:56:47 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

int	count_visible_boxes(int *line)
{
	int	max_height;
	int	count;
	int	i;

	max_height = 0;
	count = 0;
	i = 0;
	while (i < SIZE)
	{
		if (line[i] > max_height)
		{
			max_height = line[i];
			count++;
		}
		i++;
	}
	return (count);
}

int	check_row_visibility(int grid[SIZE][SIZE], int clues[SIZE *4])
{
	int	temp[SIZE];
	int	i;
	int	j;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			temp[j] = grid[i][j];
			j++;
		}
		if (count_visible_boxes(temp) != clues[8 + i])
			return (0);
		j = 0;
		while (j < SIZE)
		{
			temp[j] = grid[i][SIZE - 1 - j];
			j++;
		}
		if (count_visible_boxes(temp) != clues[12 + i])
			return (0);
		i++;
	}
	return (1);
}

int	check_col_visibility(int grid[SIZE][SIZE], int clues[SIZE *4])
{
	int	temp[SIZE];
	int	j;
	int	i;

	j = 0;
	while (j < SIZE)
	{
		i = 0;
		while (i < SIZE)
		{
			temp[i] = grid[i][j];
			i++;
		}
		if (count_visible_boxes(temp) != clues[j])
			return (0);
		i = 0;
		while (i < SIZE)
		{
			temp[i] = grid[SIZE - 1 - i][j];
			i++;
		}
		if (count_visible_boxes(temp) != clues[4 + j])
			return (0);
		j++;
	}
	return (1);
}

int	check_visibility(int grid[SIZE][SIZE], int clues[SIZE *4])
{
	if (!check_row_visibility(grid, clues))
		return (0);
	if (!check_col_visibility(grid, clues))
		return (0);
	return (1);
}
