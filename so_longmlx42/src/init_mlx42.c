/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx42.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:16:13 by raulsanc          #+#    #+#             */
/*   Updated: 2025/11/08 18:16:21 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "MLX42/MLX42.h"

#define TILE 32

static void	key_hook(mlx_key_data_t key, void *param)
{
	t_game	*g;

	g = (t_game *)param;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_RELEASE)
		mlx_close_window((mlx_t *)g->mlx);
}

static void	cleanup_and_exit(t_game *g)
{
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
	mlx_key_hook(mlx, &key_hook, g);
	return (0);
}

int	game_loop(t_game *g)
{
	mlx_loop((mlx_t *)g->mlx);
	cleanup_and_exit(g);
	return (0);
}
