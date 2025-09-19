/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 03:39:26 by raulsanc          #+#    #+#             */
/*   Updated: 2025/09/18 03:39:28 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	put_error(const char *msg)
{
	size_t	i;

	write(2, "Error\n", 6);
	i = 0;
	while (msg && msg[i])
		i++;
	write(2, msg, i);
	write(2, "\n", 1);
	return (0);
}

static int	valid_chars_and_counts(t_game *g, int *p, int *c, int *e)
{
	int		y;
	int		x;
	char	ch;

	*p = 0;
	*c = 0;
	*e = 0;
	y = 0;
	while (y < g->map_h)
	{
		if (!g->map[y][0])
			return (put_error("empty line in map"));
		x = 0;
		while ((ch = g->map[y][x]) != '\0')
		{
			if (ch != '0' && ch != '1' && ch != 'C'
				&& ch != 'E' && ch != 'P')
				return (put_error("invalid character in map"));
			if (ch == 'P')
				(*p)++;
			else if (ch == 'C')
				(*c)++;
			else if (ch == 'E')
				(*e)++;
			x++;
		}
		y++;
	}
	return (1);
}

static int	is_rectangular(t_game *g)
{
	int	y;
	int	w;
	int	len;

	w = g->map_w;
	if (w <= 0 || g->map_h <= 0)
		return (put_error("map is empty"));
	y = 0;
	while (y < g->map_h)
	{
		len = 0;
		while (g->map[y][len])
			len++;
		if (len != w)
			return (put_error("map is not rectangular"));
		y++;
	}
	return (1);
}

static int	walls_closed(t_game *g)
{
	int	y;
	int	x;
	int	w;
	int	h;

	w = g->map_w;
	h = g->map_h;
	x = 0;
	while (x < w)
	{
		if (g->map[0][x] != '1' || g->map[h - 1][x] != '1')
			return (put_error("map not closed by walls"));
		x++;
	}
	y = 0;
	while (y < h)
	{
		if (g->map[y][0] != '1' || g->map[y][w - 1] != '1')
			return (put_error("map not closed by walls"));
		y++;
	}
	return (1);
}

int	validate_map(t_game *g)
{
	int	p;
	int	c;
	int	e;

	if (!is_rectangular(g))
		return (0);
	if (!valid_chars_and_counts(g, &p, &c, &e))
		return (0);
	if (p != 1)
		return (put_error("there must be exactly 1 P"));
	if (c < 1)
		return (put_error("at least 1 C required"));
	if (e < 1)
		return (put_error("at least 1 E required"));
	if (!walls_closed(g))
		return (0);
	if (!map_has_valid_path(g))
		return (put_error("no valid path to collect all C and reach E"), 0);
	return (1);
}