/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:50:44 by raulsanc          #+#    #+#             */
/*   Updated: 2025/12/02 23:10:00 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Check that the top and bottom rows are all walls */
static int	check_top_bottom(t_game *g)
{
	int	i;

	i = 0;
	while (i < g->cols)
	{
		if (g->map[0][i] != '1' || g->map[g->rows - 1][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

/* Check that the first and last column of each row are walls */
static int	check_sides(t_game *g)
{
	int	i;

	i = 0;
	while (i < g->rows)
	{
		if (g->map[i][0] != '1' || g->map[i][g->cols - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

/* Verify that the map is completely surrounded by walls */
int	is_closed_by_walls(t_game *g)
{
	if (!check_top_bottom(g))
		return (0);
	if (!check_sides(g))
		return (0);
	return (1);
}
