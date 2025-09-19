/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 03:40:00 by raulsanc          #+#    #+#             */
/*   Updated: 2025/09/18 03:40:02 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**dup_map(char **m, int h)
{
	char	**cpy;
	int		y;
	size_t	len;

	cpy = (char **)malloc((h + 1) * sizeof(char *));
	if (!cpy)
		return (NULL);
	y = 0;
	while (y < h)
	{
		len = strlen(m[y]);
		cpy[y] = (char *)malloc(len + 1);
		if (!cpy[y])
		{
			while (--y >= 0)
				free(cpy[y]);
			free(cpy);
			return (NULL);
		}
		memcpy(cpy[y], m[y], len + 1);
		y++;
	}
	cpy[h] = NULL;
	return (cpy);
}

static void	free_m(char **m)
{
	int	i;

	i = 0;
	if (!m)
		return ;
	while (m[i])
	{
		free(m[i]);
		i++;
	}
	free(m);
}

static int	find_player(char **mm, int w, int h, int *sx, int *sy)
{
	int	x;
	int	y;

	*sx = -1;
	*sy = -1;
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			if (mm[y][x] == 'P')
			{
				*sx = x;
				*sy = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

static int	count_collectibles(char **mm, int w, int h)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			if (mm[y][x] == 'C')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

typedef struct s_bfs
{
	int	*qx;
	int	*qy;
	int	qb;
	int	qe;
	int	need_c;
	int	exit_found;
}	t_bfs;

static void	process_cell(char **mm, t_bfs *b, int x, int y, int w, int h)
{
	char	c;

	if (x < 0 || y < 0 || x >= w || y >= h)
		return ;
	c = mm[y][x];
	if (c == '1' || c == 'V')
		return ;
	if (c == 'C')
		b->need_c--;
	if (c == 'E')
		b->exit_found = 1;
	mm[y][x] = 'V';
	b->qx[b->qe] = x;
	b->qy[b->qe] = y;
	b->qe++;
}

static int	run_bfs(char **mm, int w, int h, int sx, int sy, int need_c)
{
	t_bfs	b;
	int		x;
	int		y;

	b.qx = (int *)malloc(w * h * sizeof(int));
	b.qy = (int *)malloc(w * h * sizeof(int));
	if (!b.qx || !b.qy)
		return (free(b.qx), free(b.qy), 0);
	b.qb = 0;
	b.qe = 0;
	b.need_c = need_c;
	b.exit_found = 0;
	b.qx[b.qe] = sx;
	b.qy[b.qe] = sy;
	b.qe++;
	mm[sy][sx] = 'V';
	while (b.qb < b.qe)
	{
		x = b.qx[b.qb];
		y = b.qy[b.qb];
		b.qb++;
		process_cell(mm, &b, x + 1, y, w, h);
		process_cell(mm, &b, x - 1, y, w, h);
		process_cell(mm, &b, x, y + 1, w, h);
		process_cell(mm, &b, x, y - 1, w, h);
	}
	free(b.qx);
	free(b.qy);
	return (b.need_c == 0 && b.exit_found);
}

int	map_has_valid_path(t_game *g)
{
	char	**mm;
	int		sx;
	int		sy;
	int		need_c;
	int		ok;

	mm = dup_map(g->map, g->map_h);
	if (!mm)
		return (0);
	if (!find_player(mm, g->map_w, g->map_h, &sx, &sy))
		return (free_m(mm), 0);
	need_c = count_collectibles(mm, g->map_w, g->map_h);
	ok = run_bfs(mm, g->map_w, g->map_h, sx, sy, need_c);
	free_m(mm);
	return (ok);
}
