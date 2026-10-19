/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycating_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorente <mmorente@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 12:10:26 by mmorente          #+#    #+#             */
/*   Updated: 2026/09/25 11:55:09 by mmorente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

void	init_dda_x(t_data *data, t_ray *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player.x)
			* ray->delta_dist_x;
	}
}

void	init_dda_y(t_data *data, t_ray *ray)
{
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player.y)
			* ray->delta_dist_y;
	}
}

void	init_dda(t_data *data, t_ray *ray)
{
	ray->map_x = (int)data->player.x;
	ray->map_y = (int)data->player.y;
	init_dda_x(data, ray);
	init_dda_y(data, ray);
}

t_img	*choose_wall_texture(t_ray *ray, t_data *data)
{
	if (ray->side == 0 && ray->ray_dir_x > 0)
		return (&data->map.images.textures[EAST]);
	else if (ray->side == 0)
		return (&data->map.images.textures[WEST]);
	else if (ray->ray_dir_y > 0)
		return (&data->map.images.textures[SOUTH]);
	else
		return (&data->map.images.textures[NORTH]);
}
