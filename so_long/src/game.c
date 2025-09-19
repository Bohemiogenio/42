/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 03:13:34 by raulsanc          #+#    #+#             */
/*   Updated: 2025/09/18 03:13:36 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	putnbr_line(int n)
{
	char	buf[32];
	int		i;
	long	nb;

	i = 31;
	buf[i--] = '\n';
	nb = n;
	if (nb == 0)
		buf[i--] = '0';
	if (nb < 0)
		nb = -nb;
	while (nb > 0)
	{
		buf[i--] = '0' + (nb % 10);
		nb /= 10;
	}
	write(1, "Moves: ", 7);
	if (n < 0)
		write(1, "-", 1);
	write(1, buf + i + 1, 31 - i);
}

int	init_game_state(t_game *g)
{
	int	y;
	int	x;

	g->px = -1;
	g->py = -1;
	g->coins = 0;
	g->moves = 0;
	y = 0;
	while (y < g->map_h)
	{
		x = 0;
		while (x < g->map_w)
		{
			if (g->map[y][x] == 'P')
			{
				g->px = x;
				g->py = y;
			}
			else if (g->map[y][x] == 'C')
				g->coins++;
			x++;
		}
		y++;
	}
	if (g->px == -1)
		return (put_error("player 'P' not found"));
	return (1);
}

static void	do_move(t_game *g, int nx, int ny)
{
	g->map[g->py][g->px] = '0';
	g->map[ny][nx] = 'P';
	g->px = nx;
	g->py = ny;
	g->moves++;
	putnbr_line(g->moves);
	render_map(g);
}

int	try_move(t_game *g, int dx, int dy)
{
	int		nx;
	int		ny;
	char	tile;

	nx = g->px + dx;
	ny = g->py + dy;
	if (nx < 0 || ny < 0 || nx >= g->map_w || ny >= g->map_h)
		return (0);
	tile = g->map[ny][nx];
	if (tile == '1')
		return (0);
	if (tile == 'C')
		g->coins--;
	if (tile == 'E')
	{
		if (g->coins == 0)
		{
			g->moves++;
			putnbr_line(g->moves);
			write(1, "You win!\n", 9);
			on_close(g);
			return (1);
		}
		return (0);
	}
	do_move(g, nx, ny);
	return (1);
}
