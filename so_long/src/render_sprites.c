/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:31:39 by raulsanc          #+#    #+#             */
/*   Updated: 2025/12/02 23:10:00 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	draw_cell(t_game *g, int x, int y)
{
	if (g->map[y][x] == '1')
		mlx_image_to_window(g->mlx, g->img_wall,
			x * TILE_SIZE, y * TILE_SIZE);
	else
		mlx_image_to_window(g->mlx, g->img_floor,
			x * TILE_SIZE, y * TILE_SIZE);
	if (g->map[y][x] == 'C')
		mlx_image_to_window(g->mlx, g->img_collect,
			x * TILE_SIZE, y * TILE_SIZE);
	if (g->map[y][x] == 'E')
		mlx_image_to_window(g->mlx, g->img_exit,
			x * TILE_SIZE, y * TILE_SIZE);
}

void	render_map(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < g->rows)
	{
		x = 0;
		while (x < g->cols)
		{
			draw_cell(g, x, y);
			x++;
		}
		y++;
	}
	mlx_image_to_window(g->mlx, g->img_player,
		g->player_x * TILE_SIZE, g->player_y * TILE_SIZE);
}

int	render_sprites_init(t_game *g)
{
	(void)g;
	return (1);
}
