/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 00:00:00 by rsanchez          #+#    #+#             */
/*   Updated: 2026/10/02 00:00:00 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Funcion publica y unico punto de entrada de toda la parte A
** (parser). Esto es lo unico que Persona B (o nuestro propio
** main de pruebas) necesita llamar: abre el archivo, parsea la
** configuracion y el mapa, y deja "data" listo para renderizar.
** Si algo falla en cualquier paso, la propia funcion llamada
** imprime el error, libera su memoria y termina el programa
** (parse_error nunca vuelve), asi que aqui no hace falta
** comprobar nada despues de cada llamada.
*/
void	parse_map(char *filename, t_data *data)
{
	open_cub_file(filename, data);
	parse_config(data);
	validate_map_chars(data);
	normalize_map(data);
	locate_player(data);
	check_map_closed(data);
}
