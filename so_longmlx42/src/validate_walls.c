/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:01:18 by raulsanc          #+#    #+#             */
/*   Updated: 2025/11/08 18:08:55 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	row_all_ones(const char *row, int cols)
{
	int	i;

	if (!row || cols <= 0)
		return (0);
	i = 0;
	while (i < cols)
	{
		if (row[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

static int	sides_are_ones(char **map, int rows, int cols)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		if (map[i][0] != '1' || map[i][cols - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	is_closed_by_walls(t_game *g)
{
	if (!g || !g->map || g->rows <= 0 || g->cols <= 0)
		return (0);
	if (!row_all_ones(g->map[0], g->cols))
		return (0);
	if (!row_all_ones(g->map[g->rows - 1], g->cols))
		return (0);
	if (!sides_are_ones(g->map, g->rows, g->cols))
		return (0);
	return (1);
}
