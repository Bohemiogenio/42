/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_rect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:37:35 by raulsanc          #+#    #+#             */
/*   Updated: 2025/11/08 17:04:16 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* flag validate map*/
int	is_rectangular(t_game *g)
{
	int		i;
	size_t	len;

	if (!g || !g->map || g->rows <= 0 || g->cols <= 0)
		return (0);
	i = 0;
	while (i < g->rows)
	{
		len = ft_strlen(g->map[i]);
		if ((int)len != g->cols || len == 0)
			return (0);
		i++;
	}
	return (1);
}
