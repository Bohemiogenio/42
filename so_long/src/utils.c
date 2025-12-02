/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 20:40:00 by raulsanc          #+#    #+#             */
/*   Updated: 2025/12/02 23:40:00 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Print current number of moves to standard output */
void	print_moves(t_game *g)
{
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(g->moves, 1);
	ft_putstr_fd("\n", 1);
}

/* Free all MLX images used in the game */
static void	free_images(t_game *g)
{
	if (!g->mlx)
		return ;
	if (g->img_floor)
		mlx_delete_image(g->mlx, g->img_floor);
	if (g->img_wall)
		mlx_delete_image(g->mlx, g->img_wall);
	if (g->img_player)
		mlx_delete_image(g->mlx, g->img_player);
	if (g->img_collect)
		mlx_delete_image(g->mlx, g->img_collect);
	if (g->img_exit)
		mlx_delete_image(g->mlx, g->img_exit);
	g->img_floor = NULL;
	g->img_wall = NULL;
	g->img_player = NULL;
	g->img_collect = NULL;
	g->img_exit = NULL;
}

/* Free all MLX textures used in the game */
static void	free_textures(t_game *g)
{
	if (g->tx_floor)
		mlx_delete_texture(g->tx_floor);
	if (g->tx_wall)
		mlx_delete_texture(g->tx_wall);
	if (g->tx_player)
		mlx_delete_texture(g->tx_player);
	if (g->tx_collect)
		mlx_delete_texture(g->tx_collect);
	if (g->tx_exit)
		mlx_delete_texture(g->tx_exit);
	g->tx_floor = NULL;
	g->tx_wall = NULL;
	g->tx_player = NULL;
	g->tx_collect = NULL;
	g->tx_exit = NULL;
}

/* Free all allocated resources: map, images, textures and MLX */
void	free_all(t_game *g)
{
	if (g->map)
	{
		free_map(g->map, g->rows);
		g->map = NULL;
	}
	free_images(g);
	free_textures(g);
	if (g->mlx)
	{
		mlx_terminate(g->mlx);
		g->mlx = NULL;
	}
}

/* Print an error message, free resources and exit the program */
void	exit_error(t_game *g, const char *msg)
{
	write(2, "Error\n", 6);
	if (msg)
	{
		ft_putstr_fd((char *)msg, 2);
		ft_putstr_fd("\n", 2);
	}
	free_all(g);
	exit(1);
}
