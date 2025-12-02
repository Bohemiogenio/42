/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:53:25 by raulsanc          #+#    #+#             */
/*   Updated: 2025/12/02 23:10:00 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_game(t_game *g)
{
	g->map = NULL;
	g->rows = 0;
	g->cols = 0;
	g->mlx = NULL;
	g->tx_floor = NULL;
	g->tx_wall = NULL;
	g->tx_player = NULL;
	g->tx_collect = NULL;
	g->tx_exit = NULL;
	g->img_floor = NULL;
	g->img_wall = NULL;
	g->img_player = NULL;
	g->img_collect = NULL;
	g->img_exit = NULL;
	g->player_x = 0;
	g->player_y = 0;
	g->total_collect = 0;
	g->collected = 0;
	g->moves = 0;
}

static void	check_map(t_game *g, char *path)
{
	if (!has_ber_extension(path))
		exit_error(g, "Invalid extension");
	if (!load_map(path, g))
		exit_error(g, "Map loading failed");
	if (!is_rectangular(g))
		exit_error(g, "Map is not rectangular");
	if (!validate_charset_counts(g))
		exit_error(g, "Invalid characters or counts");
	if (!is_closed_by_walls(g))
		exit_error(g, "Map is not closed by walls");
	if (!validate_path(g))
		exit_error(g, "No valid path");
}

int	main(int argc, char **argv)
{
	t_game	g;

	if (argc != 2)
	{
		write(2, "Error\nInvalid arguments\n", 24);
		return (1);
	}
	init_game(&g);
	check_map(&g, argv[1]);
	if (!game_open_window(&g))
		exit_error(&g, "MLX init failed");
	if (!render_sprites_init(&g))
		exit_error(&g, "Sprites init failed");
	mlx_key_hook(g.mlx, &handle_input, &g);
	render_map(&g);
	mlx_loop(g.mlx);
	free_all(&g);
	return (0);
}
