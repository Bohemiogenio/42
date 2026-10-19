/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorente <mmorente@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 11:43:38 by mmorente          #+#    #+#             */
/*   Updated: 2026/09/25 12:02:00 by mmorente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

void	calc_tex_x(t_data *data, t_ray *ray, t_img *tex)
{
	if (ray->side == 0)
		ray->wall_x = data->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = data->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->text_x = (int)(ray->wall_x * (double)tex->width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->text_x = tex->width - ray->text_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->text_x = tex->width - ray->text_x - 1;
}

void	draw_wall_textured(t_data *data, t_ray *ray, t_img *tex, int x)
{
	int		y;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		color;

	step = (double)tex->height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT
			/ 2.0 + ray->line_height / 2.0) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		tex_pos += step;
		color = get_texture_color(tex, ray->text_x, tex_y);
		my_pixel_put(&data->screen, x, y, color);
		y++;
	}
}
