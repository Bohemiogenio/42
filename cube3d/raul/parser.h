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
# include <math.h>

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

/*
** t_point: un nodo de la pila usada en el flood fill para
** comprobar que el mapa esta cerrado. Guarda una coordenada
** (y, x) pendiente de visitar.
*/
typedef struct s_point
{
	int				y;
	int				x;
	struct s_point	*next;
}	t_point;

/*
** t_flood_ctx: agrupa todo lo que necesita el flood fill en un
** solo puntero, para no superar el limite de 4 parametros por
** funcion que exige la Norma.
*/
typedef struct s_flood_ctx
{
	t_data	*data;		/* struct maestra, para poder leer el mapa */
	int		**visited;	/* matriz de "ya visitado" (0 o 1) */
	t_point	*stack;		/* pila de coordenadas pendientes de explorar */
	t_point	*current;	/* nodo que se esta expandiendo ahora mismo */
}	t_flood_ctx;

/*
** t_config_flags: marca que lineas de configuracion (NO/SO/WE/EA/
** F/C) ya han aparecido, para detectar duplicados y, al final,
** que no falte ninguna.
*/
typedef struct s_config_flags
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
}	t_config_flags;

/*
** t_config_ctx: agrupa todo lo que necesita el parseo de la
** configuracion en un solo puntero (como t_flood_ctx). "lines"
** es un puntero AL PUNTERO de la lista que queda por procesar,
** para poder liberarla entera si hay que abortar con error.
*/
typedef struct s_config_ctx
{
	t_data			*data;
	t_config_flags	*flags;
	t_lnode			**lines;
}	t_config_ctx;

/* Manejo de errores */
void	parse_error(t_data *data, char *msg);

/* Argumentos y apertura de archivo */
int		check_extension(char *filename);
int		open_cub_file(char *filename, t_data *data);

/* Lectura de lineas y parseo del mapa: dimensiones, validacion */
t_lnode	*read_all_lines(int fd);
int		fill_map_grid(t_data *data, t_lnode *lines);
void	compute_map_width(t_map *map);
void	validate_map_chars(t_data *data);
void	normalize_map(t_data *data);
void	locate_player(t_data *data);

/* Utilidades de parseo de configuracion */
int		is_blank_line(char *line);
int		match_id(char *line, char *id);
void	config_error(t_config_ctx *ctx, char *msg);

/* Parseo de la configuracion: texturas (NO/SO/WE/EA) y colores (F/C) */
int		set_no(t_config_ctx *ctx, char *line);
int		set_so(t_config_ctx *ctx, char *line);
int		set_we(t_config_ctx *ctx, char *line);
int		set_ea(t_config_ctx *ctx, char *line);
int		set_floor_color(t_config_ctx *ctx, char *line);
int		set_ceiling_color(t_config_ctx *ctx, char *line);
void	parse_config(t_data *data);

/* Flood fill: comprobar que el mapa esta cerrado */
int		**alloc_visited(t_map *map);
void	free_visited(int **visited, int height);
t_point	*new_point(int y, int x);
void	check_map_closed(t_data *data);

/* Liberacion de memoria */
void	free_map(t_map *map);
void	free_data(t_data *data);

/* Punto de entrada unico de todo el parser */
void	parse_map(char *filename, t_data *data);

#endif
