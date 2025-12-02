/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:20:39 by raulsanc          #+#    #+#             */
/*   Updated: 2025/12/02 23:40:00 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Disable the collectible image at map position (x, y) */
static void	hide_collect(t_game *g, int x, int y)
{
	size_t	i;
	int		px;
	int		py;

	if (!g->img_collect)
		return ;
	px = x * TILE_SIZE;
	py = y * TILE_SIZE;
	i = 0;
	while (i < g->img_collect->count)
	{
		if (g->img_collect->instances[i].x == px
			&& g->img_collect->instances[i].y == py
			&& g->img_collect->instances[i].enabled)
		{
			g->img_collect->instances[i].enabled = false;
			return ;
		}
		i++;
	}
}

/* Handle picking up a collectible at position (x, y) */
static void	collect_item(t_game *g, int x, int y)
{
	g->collected++;
	g->map[y][x] = '0';
	hide_collect(g, x, y);
}

/* Update player position and image instance, and print moves */
static void	update_player_pos(t_game *g, int x, int y)
{
	g->player_x = x;
	g->player_y = y;
	g->img_player->instances[0].x = x * TILE_SIZE;
	g->img_player->instances[0].y = y * TILE_SIZE;
	g->moves++;
	print_moves(g);
}

/* Apply movement logic for the player and handle exit condition */
static void	move_player(t_game *g, int dx, int dy)
{
	int		new_x;
	int		new_y;
	char	tile;

	new_x = g->player_x + dx;
	new_y = g->player_y + dy;
	if (new_x < 0 || new_y < 0 || new_x >= g->cols || new_y >= g->rows)
		return ;
	tile = g->map[new_y][new_x];
	if (tile == '1')
		return ;
	if (tile == 'C')
		collect_item(g, new_x, new_y);
	update_player_pos(g, new_x, new_y);
	if (tile == 'E' && g->collected == g->total_collect)
	{
		ft_putstr_fd("You win!\n", 1);
		mlx_close_window(g->mlx);
	}
}

/* MLX key hook: handle keyboard input events */
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
