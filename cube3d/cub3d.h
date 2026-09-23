/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 00:00:00 by rsanchez          #+#    #+#             */
/*   Updated: 2026/09/18 00:00:00 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
** t_map
** Rellenada por: PERSONA A (parser)
** Leida por:     PERSONA B (renderer / raycasting)
*/
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color[3];
	int		ceiling_color[3];
}	t_map;

/*
** t_player
** Inicializada por: PERSONA A (parser) -> posicion/orientacion spawn
** Actualizada por:  PERSONA B (renderer) -> movimiento, rotacion
*/
typedef struct s_player
{
	double	x;
	double	y;
	double	dir_angle;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

/*
** t_data
** Estructura maestra: se pasa por referencia a TODAS las
** funciones, tanto de parseo como de render.
*/
typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			fd;
	t_map		map;
	t_player	player;
}	t_data;

#endif
