/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorente <mmorente@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 11:28:18 by mmorente          #+#    #+#             */
/*   Updated: 2026/10/08 19:18:46 by martinmv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

void	destroy_images(t_data *data)
{
	t_images	*images;

	images = &data->map.images;
	if (images->textures[NORTH].img_ptr)
		mlx_destroy_image(data->mlx, images->textures[NORTH].img_ptr);
	if (images->textures[SOUTH].img_ptr)
		mlx_destroy_image(data->mlx, images->textures[SOUTH].img_ptr);
	if (images->textures[EAST].img_ptr)
		mlx_destroy_image(data->mlx, images->textures[EAST].img_ptr);
	if (images->textures[WEST].img_ptr)
		mlx_destroy_image(data->mlx, images->textures[WEST].img_ptr);
}

void	update_player(t_data *data)
{
	t_player	*p;

	p = &data->player;
	if (data->keys.w)
		move_player(data, p->dir_x * MOVE_SPEED, p->dir_y * MOVE_SPEED);
	if (data->keys.s)
		move_player(data, -p->dir_x * MOVE_SPEED, -p->dir_y * MOVE_SPEED);
	if (data->keys.d)
		move_player(data, -p->dir_y * MOVE_SPEED, p->dir_x * MOVE_SPEED);
	if (data->keys.a)
		move_player(data, p->dir_y * MOVE_SPEED, -p->dir_x * MOVE_SPEED);
	if (data->keys.right)
		rotate_player(data, MOVE_SPEED);
	if (data->keys.left)
		rotate_player(data, -MOVE_SPEED);
}

int	key_release(int keycode, t_data *data)
{
	set_key(&data->keys, keycode, 0);
	return (0);
}

void	set_key(t_keys *keys, int keycode, int value)
{
	if (keycode == KEY_W)
		keys->w = value;
	if (keycode == KEY_A)
		keys->a = value;
	if (keycode == KEY_S)
		keys->s = value;
	if (keycode == KEY_D)
		keys->d = value;
	if (keycode == KEY_LEFT)
		keys->left = value;
	if (keycode == KEY_RIGHT)
		keys->right = value;
}
