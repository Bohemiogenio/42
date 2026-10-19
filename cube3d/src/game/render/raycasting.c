/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorente <mmorente@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 12:01:44 by mmorente          #+#    #+#             */
/*   Updated: 2026/09/25 11:55:29 by mmorente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

void	calc_ray_direction(t_data *data, t_ray *ray, int x)
{
	t_player	*player;

	player = &data->player;
	ray->camera_x = 2.0 * x / (double)WIN_WIDTH - 1.0;
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
}

void	perform_dda(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map.grid[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

void	calc_wall_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

void	draw_column(t_data *data, t_ray *ray, int x)
{
	int		y;
	int		color_ceiling;
	int		color_floor;
	t_img	*tex;

	color_ceiling = rgb_to_int(data->map.ceiling_color[0],
			data->map.ceiling_color[1], data->map.ceiling_color[2]);
	color_floor = rgb_to_int(data->map.floor_color[0],
			data->map.floor_color[1], data->map.floor_color[2]);
	tex = choose_wall_texture(ray, data);
	calc_tex_x(data, ray, tex);
	y = 0;
	while (y < ray->draw_start)
	{
		my_pixel_put(&data->screen, x, y, color_ceiling);
		y++;
	}
	draw_wall_textured(data, ray, tex, x);
	y = ray->draw_end + 1;
	while (y < WIN_HEIGHT)
	{
		my_pixel_put(&data->screen, x, y, color_floor);
		y++;
	}
}
