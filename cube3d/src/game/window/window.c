/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorente <mmorente@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 13:45:38 by mmorente          #+#    #+#             */
/*   Updated: 2026/09/28 12:50:44 by mmorente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

int	close_window(t_data *data)
{
	free_program(data);
	if (data->screen.img_ptr)
		mlx_destroy_image(data->mlx, data->screen.img_ptr);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
		close_window(data);
	set_key(&data->keys, keycode, 1);
	return (0);
}

void	controls(t_data *data)
{
	mlx_hook(data->win, 17, 1L << 17, (int (*)())(void *)close_window, data);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
}

void	window(t_data *data)
{
	controls(data);
	mlx_loop(data->mlx);
}
