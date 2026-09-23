/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 00:00:00 by rsanchez          #+#    #+#             */
/*   Updated: 2026/09/22 00:00:00 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Devuelve la longitud de la linea sin contar el '\n' final */
static int	line_len_no_nl(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	return (len);
}

/* Calcula el ancho del mapa: la longitud de la fila mas larga */
void	compute_map_width(t_map *map)
{
	int	i;
	int	len;

	map->width = 0;
	i = 0;
	while (map->grid[i])
	{
		len = line_len_no_nl(map->grid[i]);
		if (len > map->width)
			map->width = len;
		i++;
	}
}

/* Comprueba si un caracter es uno de los 6 permitidos por el subject */
static int	is_valid_map_char(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

/* Recorre todo el mapa y lanza error si hay algun caracter invalido */
void	validate_map_chars(t_data *data)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (data->map.grid[i])
	{
		len = line_len_no_nl(data->map.grid[i]);
		j = 0;
		while (j < len)
		{
			if (!is_valid_map_char(data->map.grid[i][j]))
				parse_error(data, "invalid character found in map");
			j++;
		}
		i++;
	}
}
