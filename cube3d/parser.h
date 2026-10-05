/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 00:00:00 by rsanchez          #+#    #+#             */
/*   Updated: 2026/09/18 00:00:00 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/*
** t_lnode: nodo de lista enlazada, usado solo internamente
** para recolectar las lineas del mapa mientras se leen
** (no forma parte del contrato con Persona B).
*/
typedef struct s_lnode
{
	char			*line;
	struct s_lnode	*next;
}	t_lnode;

/* Manejo de errores */
void	parse_error(t_data *data, char *msg);

/* Argumentos y apertura de archivo */
int		check_extension(char *filename);
int		open_cub_file(char *filename, t_data *data);

/* Parseo del mapa: lectura, dimensiones, validacion */
int		fill_map_grid(t_data *data);
void	compute_map_width(t_map *map);
void	validate_map_chars(t_data *data);

/* Liberacion de memoria */
void	free_map(t_map *map);
void	free_data(t_data *data);

#endif