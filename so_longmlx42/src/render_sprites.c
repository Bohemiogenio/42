/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Raulsanc <raulsanc@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:31:39 by Raulsanc          #+#    #+#             */
/*   Updated: 2025/11/11 13:33:24 by Raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <MLX42/MLX42.h>

#define TILE 32

static int	load_img(mlx_t *mlx, const char *path, mlx_image_t **out)
{
	mlx_texture_t	*tx;
	mlx_image_t		*img;

	tx = mlx_load_png(path);
	if (!tx)
		return (1);
	img = mlx_texture_to_image(mlx, tx);
	mlx_delete_texture(tx);
	if (!img)
		return (1);
	*out = img;
	return (0);
}

int	render_sprites_init(t_game *g)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)g->mlx;
	if (load_img(mlx, "assets/floor.png", (mlx_image_t **)&g->img_floor))
		return (1);
	if (load_img(mlx, "assets/wall.png", (mlx_image_t **)&g->img_wall))
		return (1);
	if (load_img(mlx, "assets/player.png", (mlx_image_t **)&g->img_player))
		return (1);
	if (load_img(mlx, "assets/collect.png", (mlx_image_t **)&g->img_collect))
		return (1);
	if (load_img(mlx, "assets/exit.png", (mlx_image_t **)&g->img_exit))
		return (1);
	return (0);
}

static void	put_cell(t_game *g, int y, int x)
{
	mlx_t		*mlx;
	mlx_image_t	*floor;
	mlx_image_t	*wall;

	mlx = (mlx_t *)g->mlx;
	floor = (mlx_image_t *)g->img_floor;
	wall = (mlx_image_t *)g->img_wall;
	mlx_image_to_window(mlx, floor, x * TILE, y * TILE);
	if (g->map[y][x] == '1')
		mlx_image_to_window(mlx, wall, x * TILE, y * TILE);
	else if (g->map[y][x] == 'P')
		mlx_image_to_window(mlx, (mlx_image_t *)g->img_player, x * TILE, y * TILE);
	else if (g->map[y][x] == 'C')
		mlx_image_to_window(mlx, (mlx_image_t *)g->img_collect, x * TILE, y * TILE);
	else if (g->map[y][x] == 'E')
		mlx_image_to_window(mlx, (mlx_image_t *)g->img_exit, x * TILE, y * TILE);
}

int	render_sprites_draw(t_game *g)
{
	int	y;
	int	x;

	y = 0;
	while (y < g->rows)
	{
		x = 0;
		while (x < g->cols)
		{
			put_cell(g, y, x);
			x++;
		}
		y++;
	}
	return (0);
}
