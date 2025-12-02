/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:35:44 by raulsanc          #+#    #+#             */
/*   Updated: 2025/12/02 23:10:00 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'C'
		|| c == 'E' || c == 'P');
}

static void	process_tile(t_game *g, int x, int y, int *p_e)
{
	char	c;

	c = g->map[y][x];
	if (!is_valid_char(c))
		p_e[0] = -100;
	if (c == 'P')
	{
		g->player_x = x;
		g->player_y = y;
		p_e[0]++;
	}
	if (c == 'E')
		p_e[1]++;
	if (c == 'C')
		g->total_collect++;
}

int	validate_charset_counts(t_game *g)
{
	int	i;
	int	j;
	int	p_e[2];

	p_e[0] = 0;
	p_e[1] = 0;
	i = 0;
	while (i < g->rows)
	{
		j = 0;
		while (j < g->cols)
		{
			process_tile(g, j, i, p_e);
			if (p_e[0] < -10)
				return (0);
			j++;
		}
		i++;
	}
	if (p_e[0] != 1 || p_e[1] != 1)
		return (0);
	if (g->total_collect <= 0)
		return (0);
	return (1);
}
