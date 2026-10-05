/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_normalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 00:00:00 by rsanchez          #+#    #+#             */
/*   Updated: 2026/10/05 00:00:00 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Una fila esta "vacia" si solo tiene espacios o el salto de linea */
static int	is_blank_row(char *row)
{
	int	i;

	i = 0;
	while (row[i] == ' ' || row[i] == '\n')
		i++;
	return (row[i] == '\0');
}

/* Elimina las filas vacias del final del mapa (lineas en blanco) */
static void	trim_trailing_blank_rows(t_map *map)
{
	while (map->height > 0 && is_blank_row(map->grid[map->height - 1]))
	{
		free(map->grid[map->height - 1]);
		map->grid[map->height - 1] = NULL;
		map->height--;
	}
}

/* Una fila vacia en MEDIO del mapa es un error del archivo */
static void	check_no_blank_rows(t_data *data)
{
	int	i;

	i = 0;
	while (data->map.grid[i])
	{
		if (is_blank_row(data->map.grid[i]))
			parse_error(data, "empty line inside the map");
		i++;
	}
}

/*
** Crea una copia de la fila sin el '\n' final y rellena con
** espacios hasta "width" caracteres. Asi todas las filas miden
** lo mismo y quien lea grid[y][x] no se sale nunca de la fila.
*/
static char	*pad_row(char *row, int width)
{
	char	*out;
	int		i;

	out = malloc(width + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (row[i] && row[i] != '\n')
	{
		out[i] = row[i];
		i++;
	}
	while (i < width)
		out[i++] = ' ';
	out[i] = '\0';
	return (out);
}

/*
** Deja el mapa listo para entregar: sin filas vacias sobrantes,
** con el ancho recalculado y todas las filas rectangulares
** (width caracteres, sin '\n'). Si falla un malloc, el grid sigue
** siendo valido (filas ya copiadas + filas originales), asi que
** parse_error puede liberarlo sin problema.
*/
void	normalize_map(t_data *data)
{
	char	*row;
	int		i;

	trim_trailing_blank_rows(&data->map);
	check_no_blank_rows(data);
	compute_map_width(&data->map);
	i = 0;
	while (data->map.grid[i])
	{
		row = pad_row(data->map.grid[i], data->map.width);
		if (!row)
			parse_error(data, "memory allocation failed");
		free(data->map.grid[i]);
		data->map.grid[i] = row;
		i++;
	}
}
