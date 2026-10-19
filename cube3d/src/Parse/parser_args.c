/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 00:00:00 by rsanchez          #+#    #+#             */
/*   Updated: 2026/09/18 00:00:00 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	check_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

static void	init_data(t_data *data)
{
	data->fd = -1;
	data->map.grid = NULL;
	data->map.images.paths[NORTH] = NULL;
	data->map.images.paths[SOUTH] = NULL;
	data->map.images.paths[WEST] = NULL;
	data->map.images.paths[EAST] = NULL;
}

int	open_cub_file(char *filename, t_data *data)
{
	int	fd;

	init_data(data);
	if (!check_extension(filename))
		parse_error(data, "the file must have a .cub extension");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		parse_error(data, "could not open the map file");
	data->fd = fd;
	return (fd);
}
