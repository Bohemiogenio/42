/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:23:51 by raulsanc          #+#    #+#             */
/*   Updated: 2025/11/10 15:21:47 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <MLX42/MLX42.h>

#define TILE 64

static void	fill_rect(mlx_image_t *img, uint32_t color)
{
	int	x;
	int	y;

	y = 0;
	while (y < TILE)
	{
		x = 0;
		while (x < TILE)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

int	render_basic_init(t_game *g)
{
	mlx_t		*mlx;
	mlx_image_t	*floor_img;
	mlx_image_t	*wall_img;

	mlx = (mlx_t *)g->mlx;
	floor_img = mlx_new_image(mlx, TILE, TILE);
	if (!floor_img)
		return (1);
	wall_img = mlx_new_image(mlx, TILE, TILE);
	if (!wall_img)
		return (mlx_delete_image(mlx, floor_img), 1);
	fill_rect(floor_img, 0xFF2E3440); /* gris azulado (RGBA) */
	fill_rect(wall_img, 0xFF5E81AC);  /* azul más claro (RGBA) */
	g->img_floor = (void *)floor_img;
	g->img_wall = (void *)wall_img;
	return (0);
}

int	render_basic_draw(t_game *g)
{
	int			y;
	int			x;
	mlx_t		*mlx;
	mlx_image_t	*floor_img;
	mlx_image_t	*wall_img;

	mlx = (mlx_t *)g->mlx;
	floor_img = (mlx_image_t *)g->img_floor;
	wall_img = (mlx_image_t *)g->img_wall;
	y = 0;
	while (y < g->rows)
	{
		x = 0;
		while (x < g->cols)
		{
			mlx_image_to_window(mlx, floor_img, x * TILE, y * TILE);
			if (g->map[y][x] == '1')
				mlx_image_to_window(mlx, wall_img, x * TILE, y * TILE);
			x++;
		}
		y++;
	}
	return (0);
}
