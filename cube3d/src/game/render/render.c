/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorente <mmorente@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 11:21:21 by mmorente          #+#    #+#             */
/*   Updated: 2026/09/28 12:46:30 by mmorente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

void	render_column(t_data *data, int x)
{
	t_ray	ray;

	calc_ray_direction(data, &ray, x);
	init_dda(data, &ray);
	perform_dda(data, &ray);
	calc_wall_dist(&ray);
	draw_column(data, &ray, x);
}

void	render_map(t_data *data)
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		render_column(data, x);
		x++;
	}
}

int	render(t_data *data)
{
	render_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->screen.img_ptr, 0, 0);
	update_player(data);
	return (0);
}
