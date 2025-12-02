/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx42.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:30:44 by raulsanc          #+#    #+#             */
/*   Updated: 2025/12/02 23:10:00 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Load all textures from PNG files */
static int	load_textures(t_game *g)
{
	g->tx_floor = mlx_load_png("assets/floor.png");
	g->tx_wall = mlx_load_png("assets/wall.png");
	g->tx_player = mlx_load_png("assets/player.png");
	g->tx_collect = mlx_load_png("assets/collect.png");
	g->tx_exit = mlx_load_png("assets/exit.png");
	if (!g->tx_floor || !g->tx_wall || !g->tx_player
		|| !g->tx_collect || !g->tx_exit)
		return (0);
	return (1);
}

/* Convert textures to images for rendering */
static int	init_images(t_game *g)
{
	g->img_floor = mlx_texture_to_image(g->mlx, g->tx_floor);
	g->img_wall = mlx_texture_to_image(g->mlx, g->tx_wall);
	g->img_player = mlx_texture_to_image(g->mlx, g->tx_player);
	g->img_collect = mlx_texture_to_image(g->mlx, g->tx_collect);
	g->img_exit = mlx_texture_to_image(g->mlx, g->tx_exit);
	if (!g->img_floor || !g->img_wall || !g->img_player
		|| !g->img_collect || !g->img_exit)
		return (0);
	return (1);
}

/* Resize all images to the TILE_SIZE resolution */
static int	resize_images(t_game *g)
{
	if (!mlx_resize_image(g->img_floor, TILE_SIZE, TILE_SIZE))
		return (0);
	if (!mlx_resize_image(g->img_wall, TILE_SIZE, TILE_SIZE))
		return (0);
	if (!mlx_resize_image(g->img_player, TILE_SIZE, TILE_SIZE))
		return (0);
	if (!mlx_resize_image(g->img_collect, TILE_SIZE, TILE_SIZE))
		return (0);
	if (!mlx_resize_image(g->img_exit, TILE_SIZE, TILE_SIZE))
		return (0);
	return (1);
}

/* Initialize MLX window, load and prepare textures and images */
int	game_open_window(t_game *g)
{
	g->mlx = mlx_init(g->cols * TILE_SIZE, g->rows * TILE_SIZE,
			"so_long", false);
	if (!g->mlx)
		return (0);
	if (!load_textures(g))
		return (0);
	if (!init_images(g))
		return (0);
	if (!resize_images(g))
		return (0);
	return (1);
}
