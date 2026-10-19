/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorente <mmorente@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 11:29:57 by mmorente          #+#    #+#             */
/*   Updated: 2026/09/28 12:23:01 by mmorente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

void	rotate_player(t_data *data, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	data->player.dir_x = old_dir_x * cos(angle)
		- data->player.dir_y * sin(angle);
	data->player.dir_y = old_dir_x * sin(angle)
		+ data->player.dir_y * cos(angle);
	old_plane_x = data->player.plane_x;
	data->player.plane_x = old_plane_x * cos(angle)
		- data->player.plane_y * sin(angle);
	data->player.plane_y = old_plane_x * sin(angle)
		+ data->player.plane_y * cos(angle);
}

int	is_wall(t_data *data, double x, double y)
{
	return (data->map.grid[(int)y][(int)x] == '1');
}

void	move_player(t_data *data, double dx, double dy)
{
	double	margin_x;
	double	margin_y;

	margin_x = HITBOX;
	margin_y = HITBOX;
	if (dx < 0)
		margin_x = -HITBOX;
	if (dy < 0)
		margin_y = -HITBOX;
	if (!is_wall(data, data->player.x + dx + margin_x, data->player.y))
		data->player.x += dx;
	if (!is_wall(data, data->player.x, data->player.y + dy + margin_y))
		data->player.y += dy;
}
