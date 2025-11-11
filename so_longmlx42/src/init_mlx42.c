/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx42.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:16:13 by raulsanc          #+#    #+#             */
/*   Updated: 2025/11/11 19:01:44 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define TILE 64

static void	delete_images(t_game *g)
{
	mlx_t	*mlx;

	if (!g || !g->mlx)
		return ;
	mlx = (mlx_t *)g->mlx;
	if (g->img_floor)
		mlx_delete_image(mlx, (mlx_image_t *)g->img_floor);
	if (g->img_wall)
		mlx_delete_image(mlx, (mlx_image_t *)g->img_wall);
	if (g->img_player)
		mlx_delete_image(mlx, (mlx_image_t *)g->img_player);
	if (g->img_collect)
		mlx_delete_image(mlx, (mlx_image_t *)g->img_collect);
	if (g->img_exit)
		mlx_delete_image(mlx, (mlx_image_t *)g->img_exit);
	g->img_floor = NULL;
	g->img_wall = NULL;
	g->img_player = NULL;
	g->img_collect = NULL;
	g->img_exit = NULL;
}

static void	on_close(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	delete_images(g);
	if (g->mlx)
		mlx_terminate((mlx_t *)g->mlx);
	free_map(g->map, g->rows);
	exit(0);
}

int	game_open_window(t_game *g)
{
	int		w;
	int		h;
	mlx_t	*mlx;

	w = g->cols * TILE;
	h = g->rows * TILE;
	mlx = mlx_init(w, h, "so_long", false);
	if (!mlx)
		return (1);
	g->mlx = (void *)mlx;
	mlx_key_hook(mlx, &handle_input, g);
	mlx_close_hook(mlx, &on_close, g);
	return (0);
}

int	game_loop(t_game *g)
{
	mlx_loop((mlx_t *)g->mlx);
	on_close(g);
	return (0);
}
