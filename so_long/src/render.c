/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 03:39:12 by raulsanc          #+#    #+#             */
/*   Updated: 2025/09/18 03:39:15 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	load_xpm(t_game *g, t_img *dst, const char *path)
{
	dst->img = mlx_xpm_file_to_image(g->mlx, (char *)path, &dst->w, &dst->h);
	if (!dst->img)
		return (put_error("mlx_xpm_file_to_image failed"));
	if (dst->w != TILE || dst->h != TILE)
		return (put_error("texture must be 64x64"));
	return (1);
}

int	init_textures(t_game *g)
{
	if (!load_xpm(g, &g->tx.floor_, "assets/floor.xpm"))
		return (0);
	if (!load_xpm(g, &g->tx.wall, "assets/wall.xpm"))
		return (0);
	if (!load_xpm(g, &g->tx.player, "assets/player.xpm"))
		return (0);
	if (!load_xpm(g, &g->tx.exit, "assets/exit.xpm"))
		return (0);
	if (!load_xpm(g, &g->tx.coin, "assets/coin.xpm"))
		return (0);
	return (1);
}

void	destroy_textures(t_game *g)
{
	if (!g->mlx)
		return ;
	if (g->tx.floor_.img)
		mlx_destroy_image(g->mlx, g->tx.floor_.img);
	if (g->tx.wall.img)
		mlx_destroy_image(g->mlx, g->tx.wall.img);
	if (g->tx.player.img)
		mlx_destroy_image(g->mlx, g->tx.player.img);
	if (g->tx.exit.img)
		mlx_destroy_image(g->mlx, g->tx.exit.img);
	if (g->tx.coin.img)
		mlx_destroy_image(g->mlx, g->tx.coin.img);
}

static void	put_tile(t_game *g, t_img *tex, int x, int y)
{
	mlx_put_image_to_window(g->mlx, g->win, tex->img, x * TILE, y * TILE);
}

void	render_map(t_game *g)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < g->map_h)
	{
		x = 0;
		while (x < g->map_w)
		{
			c = g->map[y][x];
			put_tile(g, &g->tx.floor_, x, y);
			if (c == '1')
				put_tile(g, &g->tx.wall, x, y);
			else if (c == 'P')
				put_tile(g, &g->tx.player, x, y);
			else if (c == 'E')
				put_tile(g, &g->tx.exit, x, y);
			else if (c == 'C')
				put_tile(g, &g->tx.coin, x, y);
			x++;
		}
		y++;
	}
}
