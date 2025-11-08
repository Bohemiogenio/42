/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:11:52 by raulsanc          #+#    #+#             */
/*   Updated: 2025/11/08 18:11:59 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	find_player(t_game *g, int *py, int *px)
{
	int	y;
	int	x;

	y = 0;
	while (y < g->rows)
	{
		x = 0;
		while (x < g->cols)
		{
			if (g->map[y][x] == 'P')
				return (*py = y, *px = x, 1);
			x++;
		}
		y++;
	}
	return (0);
}

static char	**dup_map(t_game *g)
{
	char	**m;
	int		i;

	m = (char **)malloc(sizeof(char *) * g->rows);
	if (!m)
		return (NULL);
	i = 0;
	while (i < g->rows)
	{
		m[i] = ft_strdup(g->map[i]);
		if (!m[i])
			return (free_map(m, i), NULL);
		i++;
	}
	return (m);
}

static void	ffill(char **m, int y, int x, t_game *g)
{
	if (y < 0 || x < 0 || y >= g->rows || x >= g->cols)
		return ;
	if (m[y][x] == '1' || m[y][x] == 'V')
		return ;
	m[y][x] = 'V';
	ffill(m, y + 1, x, g);
	ffill(m, y - 1, x, g);
	ffill(m, y, x + 1, g);
	ffill(m, y, x - 1, g);
}

static int	unreached_exists(char **m, t_game *g)
{
	int	y;
	int	x;

	y = 0;
	while (y < g->rows)
	{
		x = 0;
		while (x < g->cols)
		{
			if (m[y][x] == 'C' || m[y][x] == 'E')
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	validate_path(t_game *g)
{
	char	**m;
	int		py;
	int		px;

	if (!find_player(g, &py, &px))
		return (0);
	m = dup_map(g);
	if (!m)
		return (0);
	ffill(m, py, px, g);
	if (unreached_exists(m, g))
		return (free_map(m, g->rows), 0);
	free_map(m, g->rows);
	return (1);
}
