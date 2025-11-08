/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:46:39 by raulsanc          #+#    #+#             */
/*   Updated: 2025/11/08 17:58:09 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P');
}

static int	process_row(const char *row, int *p, int *e, int *c)
{
	int	j;

	j = 0;
	while (row[j])
	{
		if (!is_valid_char(row[j]))
			return (0);
		if (row[j] == 'P')
			(*p)++;
		else if (row[j] == 'E')
			(*e)++;
		else if (row[j] == 'C')
			(*c)++;
		j++;
	}
	return (1);
}

int	validate_charset_counts(t_game *g)
{
	int	i;
	int	p;
	int	e;
	int	c;

	if (!g || !g->map)
		return (0);
	p = 0;
	e = 0;
	c = 0;
	i = 0;
	while (i < g->rows)
	{
		if (!process_row(g->map[i], &p, &e, &c))
			return (0);
		i++;
	}
	return (p == 1 && e == 1 && c >= 1);
}
