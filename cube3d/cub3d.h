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
** t_map: datos del mapa y la escena.
** Rellenada por: PERSONA A (parser)
** Leida por:     PERSONA B (renderer / raycasting)
*/
typedef struct s_map
{
	char	**grid;				/* mapa como array de strings */
	int		width;				/* ancho: fila mas larga */
	int		height;				/* alto: numero de filas */
	char	*no_path;			/* ruta textura Norte */
	char	*so_path;			/* ruta textura Sur */
	char	*we_path;			/* ruta textura Oeste */
	char	*ea_path;			/* ruta textura Este */
	int		floor_color[3];		/* color suelo RGB */
	int		ceiling_color[3];	/* color techo RGB */
}	t_map;

/*
** t_player: posicion y orientacion del jugador.
** Inicializada por: PERSONA A (parser) -> spawn inicial
** Actualizada por:  PERSONA B (renderer) -> movimiento
*/
typedef struct s_player
{
	double	x;			/* posicion X en el mapa */
	double	y;			/* posicion Y en el mapa */
	double	dir_angle;	/* angulo de direccion (radianes) */
	double	dir_x;		/* vector direccion X (raycasting) */
	double	dir_y;		/* vector direccion Y (raycasting) */
	double	plane_x;	/* vector plano camara X */
	double	plane_y;	/* vector plano camara Y */
}	t_player;

/*
** t_data: estructura maestra, se pasa por referencia a TODAS
** las funciones, tanto de parseo como de render.
*/
typedef struct s_data
{
	void		*mlx;	/* instancia mlx (Persona B) */
	void		*win;	/* ventana mlx (Persona B) */
	int			fd;		/* descriptor del archivo .cub abierto */
	t_map		map;	/* datos del mapa */
	t_player	player;	/* datos del jugador */
}	t_data;

#endif
