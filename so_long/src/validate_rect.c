/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_rect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:20:44 by raulsanc          #+#    #+#             */
/*   Updated: 2025/12/02 23:10:00 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_rectangular(t_game *g)
{
	int	i;
	int	len;

	if (!g->map || g->rows < 1)
		return (0);
	len = ft_strlen(g->map[0]);
	i = 1;
	while (i < g->rows)
	{
		if ((int)ft_strlen(g->map[i]) != len)
			return (0);
		i++;
	}
	g->cols = len;
	return (1);
}
