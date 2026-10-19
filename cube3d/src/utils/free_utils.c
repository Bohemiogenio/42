/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 00:00:00 by rsanchez          #+#    #+#             */
/*   Updated: 2026/09/23 00:00:00 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	free_textures(t_map *map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(map->images.paths[i]);
		map->images.paths[i++] = NULL;
	}
}

static void	free_grid(t_map *map)
{
	int	i;

	if (!map->grid)
		return ;
	i = 0;
	while (map->grid[i])
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	free_grid(map);
	free_textures(map);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	free_map(&data->map);
}
