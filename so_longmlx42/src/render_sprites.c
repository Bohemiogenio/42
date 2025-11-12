/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:31:39 by Raulsanc          #+#    #+#             */
/*   Updated: 2025/11/11 19:48:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <MLX42/MLX42.h>

#define TILE     64
#define Z_FLOOR   0
#define Z_WALL    2
#define Z_ITEM    3
#define Z_PLAYER 10

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
	if ((int)img->width != TILE || (int)img->height != TILE)
	{
		if (!mlx_resize_image(img, TILE, TILE))
			return (mlx_delete_image(mlx, img), 1);
	}
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
	g->player_inst = 0;
	return (0);
}

static void	put_cell(t_game *g, int y, int x)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			id;

	mlx = (mlx_t *)g->mlx;
	id = mlx_image_to_window(mlx, (mlx_image_t *)g->img_floor, x * TILE, y * TILE);
	((mlx_image_t *)g->img_floor)->instances[id].z = Z_FLOOR;
	if (g->map[y][x] == '1')
	{
		id = mlx_image_to_window(mlx, (mlx_image_t *)g->img_wall, x * TILE, y * TILE);
		((mlx_image_t *)g->img_wall)->instances[id].z = Z_WALL;
	}
	else if (g->map[y][x] == 'P')
	{
		id = mlx_image_to_window(mlx, (mlx_image_t *)g->img_player, x * TILE, y * TILE);
		g->player_x = x;
		g->player_y = y;
		g->player_inst = (id < 0) ? 0 : id;
		img = (mlx_image_t *)g->img_player;
		img->instances[g->player_inst].z = Z_PLAYER;
	}
	else if (g->map[y][x] == 'C')
	{
		id = mlx_image_to_window(mlx, (mlx_image_t *)g->img_collect, x * TILE, y * TILE);
		((mlx_image_t *)g->img_collect)->instances[id].z = Z_ITEM;
		g->total_collect++;
	}
	else if (g->map[y][x] == 'E')
	{
		id = mlx_image_to_window(mlx, (mlx_image_t *)g->img_exit, x * TILE, y * TILE);
		((mlx_image_t *)g->img_exit)->instances[id].z = Z_ITEM;
	}
}

int	render_sprites_draw(t_game *g)
{
	int	y;
	int	x;

	g->total_collect = 0;
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
