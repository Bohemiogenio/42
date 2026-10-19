/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorente <mmorente@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 12:16:00 by mmorente          #+#    #+#             */
/*   Updated: 2026/10/08 19:18:19 by martinmv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <math.h>

// Window size

# define WIN_WIDTH 1920

# define WIN_HEIGHT 1080

// KEYS

# define KEY_LEFT 65361

# define KEY_RIGHT 65363

# define ESC 65307

# define KEY_W 119

# define KEY_A 97

# define KEY_S 115

# define KEY_D 100

// Other options

# define MOVE_SPEED 0.05

# define HITBOX 0.2

/*
 *
 * Enum para identificar que direccion vas a rellenar
 *
 */
typedef enum e_direction
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3
}	t_direction;

/*
 * ====================
 * t_images
 *=====================
 */
typedef struct s_img
{
	void	*img_ptr; // Puntero identificando la imagen en mlx
	char	*addr; // Direccion de la textura
	int		bpp; // bits per pixel (Cuantos pixeles ocupa CADA pixel en memoria)
	int		line_len; // Cuantos bytes ocupa una fila entera de la imagen
	int		endian; // El orden en que se guardan los bytes de cada color
	int		width;
	int		height;
}	t_img;

typedef struct s_images
{
	char	*paths[4];
	t_img	textures[4]; // Persona B es la que lo inicializa
}	t_images;

/*
** ============================================================
** t_map
** ------------------------------------------------------------
** Rellenada por: PERSONA A (parser)
** Leída por:     PERSONA B (renderer / raycasting)
** ============================================================
*/
typedef struct s_map
{
	char		**grid; // mapa, array de strings (una por fila)
	int			width;	// ancho maximo del mapa (columna mas larga)
	int			height;	// numero de filas del mapa
	t_images	images;
	int			floor_color[3];	// RGB floor  [0]=R [1]=G [2]=B
	int			ceiling_color[3]; // RGB ceiling [0]=R [1]=G [2]=B
}	t_map;

/*
** ============================================================
** t_player
** ------------------------------------------------------------
** Inicializada por: PERSONA A (parser) -> posicion/orientacion spawn
** Actualizada por:  PERSONA B (renderer) -> movimiento, rotacion
** ============================================================
*/
typedef struct s_player
{
	double	x;		// posicion X en el mapa (coordenadas de casilla, doble)
	double	y;		// posicion Y en el mapa
	double	dir_angle; // angulo de direccion en radianes
	double	dir_x;		// vector direccion (para raycasting)
	double	dir_y;
	double	plane_x; // vector plano de camara
	double	plane_y;
}	t_player;

/*
 *
 * Estructura para las variables del render
 * se crea y destruye por cada columna
 *
 * */

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		text_x;
}	t_ray;

// Struct for the KEYS

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

/*
** ============================================================
** t_data
** ------------------------------------------------------------
** Estructura maestra: se pasa por referencia a TODAS las
** funciones, tanto de parseo como de render.
** ============================================================
*/
typedef struct s_data
{
	void		*mlx; // instancia mlx      -> la inicializa Persona B
	void		*win; // ventana mlx        -> la inicializa Persona B
	t_keys		keys;
	t_map		map;	// -> la rellena Persona A
	t_player	player;	// -> la inicializa Persona A, la actualiza Persona B
	t_img		screen; // Screen to paint
	int			fd;
}	t_data;

typedef struct s_config_flags
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
}	t_config_flags;

typedef struct s_point
{
	int				y;
	int				x;
	struct s_point	*next;
}	t_point;

typedef struct s_flood_ctx
{
	t_data	*data;		/* struct maestra, para poder leer el mapa */
	int		**visited;	/* matriz de "ya visitado" (0 o 1) */
	t_point	*stack;		/* pila de coordenadas pendientes de explorar */
	t_point	*current;	/* nodo que se esta expandiendo ahora mismo */
}	t_flood_ctx;

typedef struct s_lnode
{
	char			*line;
	struct s_lnode	*next;
}	t_lnode;

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

/*******************  Render functions part  ******************/
void	innitialice_graphic_data(t_data *data);
void	free_program(t_data *data);
void	window(t_data *data);
void	innitialice_screen(t_data *data);
int		innitialice_images(t_data *data);
int		close_window(t_data *data);
void	destroy_images(t_data *data);
void	init_dda(t_data *data, t_ray *ray);
int		rgb_to_int(int r, int g, int b);
t_img	*choose_wall_texture(t_ray *ray, t_data *data);
void	my_pixel_put(t_img *img, int x, int y, int color);
int		render(t_data *data);
void	calc_ray_direction(t_data *data, t_ray *ray, int x);
void	perform_dda(t_data *data, t_ray *ray);
void	calc_wall_dist(t_ray *ray);
void	draw_column(t_data *data, t_ray *ray, int x);
void	game(t_data *data);
void	draw_wall_textured(t_data *data, t_ray *ray, t_img *tex, int x);
void	calc_tex_x(t_data *data, t_ray *ray, t_img *tex);
void	rotate_player(t_data *data, double angle);
int		get_texture_color(t_img *img, int x, int y);
void	update_player(t_data *data);
void	move_player(t_data *data, double dx, double dy);
int		key_release(int keycode, t_data *data);
void	set_key(t_keys *keys, int keycode, int value);
#endif
