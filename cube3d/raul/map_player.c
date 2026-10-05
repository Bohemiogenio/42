/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 00:00:00 by rsanchez          #+#    #+#             */
/*   Updated: 2026/10/01 00:00:00 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Comprueba si un caracter es una de las 4 letras de jugador */
static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/* Calcula el angulo inicial y el vector direccion segun la letra */
static void	set_player_dir(t_data *data, char c)
{
	if (c == 'N')
		data->player.dir_angle = M_PI / 2;
	else if (c == 'S')
		data->player.dir_angle = -M_PI / 2;
	else if (c == 'E')
		data->player.dir_angle = 0;
	else
		data->player.dir_angle = M_PI;
	data->player.dir_x = cos(data->player.dir_angle);
	data->player.dir_y = sin(data->player.dir_angle);
}

/*
** Recorre todo el mapa buscando letras de jugador.
** Guarda la primera que encuentra y cuenta cuantas hay en total,
** para poder validar despues que hay exactamente una.
*/
static int	count_and_store_player(t_data *data, int *pos)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (data->map.grid[i])
	{
		j = 0;
		while (data->map.grid[i][j] && data->map.grid[i][j] != '\n')
		{
			if (is_player_char(data->map.grid[i][j]))
			{
				if (count == 0)
				{
					pos[0] = i;
					pos[1] = j;
				}
				count++;
			}
			j++;
		}
		i++;
	}
	return (count);
}

/* Localiza al jugador, valida que haya exactamente uno, y lo guarda */
void	locate_player(t_data *data)
{
	int		pos[2];
	int		count;
	char	c;

	count = count_and_store_player(data, pos);
	if (count == 0)
		parse_error(data, "no player start position found in map");
	if (count > 1)
		parse_error(data, "more than one player start position in map");
	data->player.y = pos[0];
	data->player.x = pos[1];
	c = data->map.grid[pos[0]][pos[1]];
	set_player_dir(data, c);
}
