/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 11:37:40 by raulsanc          #+#    #+#             */
/*   Updated: 2025/11/03 15:27:55 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* write msg error */
void	sl_error(const char *msg)
{
	int	i;

	i = 0;
	write(2, "Error\n", 6);
	if (msg)
	{
		while (msg[i])
		{
			write(2, &msg[i], 1);
			i++;
		}
	}
	write(2, "\n", 1);
}

/* flag .ber.png */
int	sl_has_extension(const char *path, const char *ext)
{
	int	i;
	int	j;

	if (!path || !ext)
		return (0);
	i = 0;
	while (path[i])
		i++;
	j = 0;
	while (ext[j])
		j++;
	if (j > i)
		return (0);
	while (j > 0)
	{
		if (path[i - 1] != ext[j - 1])
			return (0);
		i--;
		j--;
	}
	return (1);
}

/* exit window game */
void	sl_quit(t_game *g, int status)
{
	if (g && g->mlx)
	{
		mlx_close_window(g->mlx);
		mlx_terminate(g->mlx);
	}
	_exit(status);
}
