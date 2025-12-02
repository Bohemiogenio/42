/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:05:44 by raulsanc          #+#    #+#             */
/*   Updated: 2025/12/02 23:50:00 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Duplicate the map into a new matrix for BFS */
static char	**dup_map(t_game *g)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * g->rows);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < g->rows)
	{
		copy[i] = ft_strdup(g->map[i]);
		if (!copy[i])
		{
			free_map(copy, i);
			return (NULL);
		}
		i++;
	}
	return (copy);
}

/* Try to move BFS to a new cell if it is not a wall or visited */
static void	try_move(char **m, t_bfs *b, int x, int y)
{
	if (m[y][x] == '1' || m[y][x] == 'V')
		return ;
	m[y][x] = 'V';
	queue_push(b, x, y);
}

/* Process the current BFS tile and update collectibles and exit reachability */
static void	process_tile(t_game *g, char **m, t_bfs *b, int *c_e)
{
	int	x;
	int	y;

	x = b->qx[b->start];
	y = b->qy[b->start];
	b->start++;
	if (g->map[y][x] == 'C')
		c_e[0]++;
	if (g->map[y][x] == 'E')
		c_e[1] = 1;
	try_move(m, b, x + 1, y);
	try_move(m, b, x - 1, y);
	try_move(m, b, x, y + 1);
	try_move(m, b, x, y - 1);
}

/* Run a BFS to check that all collectibles and exit are reachable */
static int	bfs(t_game *g, char **m)
{
	t_bfs	b;
	int		c_e[2];

	b.start = 0;
	b.end = 0;
	c_e[0] = 0;
	c_e[1] = 0;
	queue_push(&b, g->player_x, g->player_y);
	m[g->player_y][g->player_x] = 'V';
	while (b.start < b.end)
		process_tile(g, m, &b, c_e);
	if (c_e[0] == g->total_collect && c_e[1] == 1)
		return (1);
	return (0);
}

/* Validate that there is a valid path through the map */
int	validate_path(t_game *g)
{
	char	**copy;
	int		result;

	copy = dup_map(g);
	if (!copy)
		return (0);
	result = bfs(g, copy);
	free_map(copy, g->rows);
	return (result);
}
