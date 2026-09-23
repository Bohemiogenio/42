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

#include "parser.h"

/* Libera las 4 rutas de textura, si estan reservadas */
static void	free_textures(t_map *map)
{
	if (map->no_path)
		free(map->no_path);
	if (map->so_path)
		free(map->so_path);
	if (map->we_path)
		free(map->we_path);
	if (map->ea_path)
		free(map->ea_path);
	map->no_path = NULL;
	map->so_path = NULL;
	map->we_path = NULL;
	map->ea_path = NULL;
}

/* Libera el grid completo: cada linea y despues el array */
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

/* Libera todo lo reservado dentro de t_map */
void	free_map(t_map *map)
{
	if (!map)
		return ;
	free_grid(map);
	free_textures(map);
}

/* Libera todo lo reservado dentro de t_data (por ahora solo el mapa) */
void	free_data(t_data *data)
{
	if (!data)
		return ;
	free_map(&data->map);
}
