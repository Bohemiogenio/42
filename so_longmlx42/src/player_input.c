/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 18:44:39 by raulsanc          #+#    #+#             */
/*   Updated: 2025/11/11 19:48:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define TILE     64
#define Z_WIPE   5  

static void	wipe_collect_tile(t_game *game, int x, int y)
{
	int	id;

	id = mlx_image_to_window((mlx_t *)game->mlx,
			(mlx_image_t *)game->img_floor, x * TILE, y * TILE);
	((mlx_image_t *)game->img_floor)->instances[id].z = Z_WIPE;
}

static void	do_collect_if_any(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'C')
	{
		game->map[y][x] = '0';
		game->collected++;
		wipe_collect_tile(game, x, y);
	}
}

static int	try_finish_if_exit(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'E' && game->collected == game->total_collect)
	{
		printf("You win in %d moves!\n", game->moves);
		mlx_close_window(game->mlx);
		return (1);
	}
	return (0);
}

static void	move_player(t_game *game, int dx, int dy)
{
	int			nx;
	int			ny;
	mlx_image_t	*img;

	nx = game->player_x + dx;
	ny = game->player_y + dy;
	if (nx < 0 || ny < 0 || ny >= game->rows || nx >= game->cols)
		return ;
	if (game->map[ny][nx] == '1')
		return ;
	do_collect_if_any(game, nx, ny);
	game->player_x = nx;
	game->player_y = ny;
	game->moves++;
	printf("Moves: %d\n", game->moves);
	if (try_finish_if_exit(game, nx, ny))
		return ;
	img = (mlx_image_t *)game->img_player;
	if (img && img->count > 0)
	{
		img->instances[game->player_inst].x = game->player_x * TILE;
		img->instances[game->player_inst].y = game->player_y * TILE;
		img->instances[game->player_inst].z = 10;
	}
}

void	handle_input(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(game->mlx);
	else if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		move_player(game, 0, -1);
	else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		move_player(game, 0, 1);
	else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		move_player(game, -1, 0);
	else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		move_player(game, 1, 0);
}
