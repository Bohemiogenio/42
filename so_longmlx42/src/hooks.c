/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 12:57:11 by raulsanc          #+#    #+#             */
/*   Updated: 2025/11/02 13:16:20 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Exit keyboard ESC */
void	sl_key_hook(mlx_key_data_t keydata, void *param)
{
	t_game *g;

	g = (t_game *)param;
	if (!g || !g->mlx)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(g->mlx);
}

/* Exit click (X) */
void	sl_close_hook(void *param)
{
	t_game *g;
	
	g = (t_game *)param;
	if(!g || !g->mlx)
		return ;
	mlx_close_window(g->mlx);
}
