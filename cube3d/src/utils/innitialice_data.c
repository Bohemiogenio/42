/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   innitialice_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorente <mmorente@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 13:38:08 by mmorente          #+#    #+#             */
/*   Updated: 2026/09/28 10:58:43 by mmorente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	innitialice_graphic_data(t_data *data)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Cub3D");
	data->mlx = mlx;
	data->win = mlx_win;
}

int	innitialice_images(t_data *data)
{
	int				i;
	t_images		*images;

	i = 0;
	images = &data->map.images;
	while (i < 4)
	{
		images->textures[i].img_ptr = mlx_xpm_file_to_image(
				data->mlx,
				images->paths[i],
				&images->textures[i].width,
				&images->textures[i].height);
		if (!images->textures[i].img_ptr)
			return (0);
		images->textures[i].addr = mlx_get_data_addr(
				images->textures[i].img_ptr,
				&images->textures[i].bpp,
				&images->textures[i].line_len,
				&images->textures[i].endian);
		i++;
	}
	return (1);
}

void	innitialice_screen(t_data *data)
{
	data->screen.img_ptr = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->screen.addr = mlx_get_data_addr(
			data->screen.img_ptr,
			&data->screen.bpp,
			&data->screen.line_len,
			&data->screen.endian
			);
	data->screen.width = WIN_WIDTH;
	data->screen.height = WIN_HEIGHT;
}
