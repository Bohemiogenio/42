/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 06:27:21 by raulsanc          #+#    #+#             */
/*   Updated: 2025/08/09 06:30:22 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include "mlx.h"

# define TILE 64

/* keycodes (X11 / Linux) */
# define K_ESC		65307
# define K_LEFT		65361
# define K_UP		65362
# define K_RIGHT	65363
# define K_DOWN		65364
# define K_W		119
# define K_A		97
# define K_S		115
# define K_D		100

typedef struct s_img
{
	void	*img;
	int		w;
	int		h;
}	t_img;

typedef struct s_textures
{
	t_img	floor_;
	t_img	wall;
	t_img	player;
	t_img	exit;
	t_img	coin;
}	t_textures;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	char		**map;
	int			map_w;
	int			map_h;
	t_textures	tx;
	int			px;
	int			py;
	int			coins;
	int			moves;
}	t_game;

/* hooks */
int		on_close(t_game *g);
int		on_key(int key, t_game *g);

/* lifecycle */
int		game_init(t_game *g, int w, int h, char *title);

/* map */
int		load_map(t_game *g, const char *path);
void	free_map(char **m);
int		validate_map(t_game *g);

/* render */
int		init_textures(t_game *g);
void	destroy_textures(t_game *g);
void	render_map(t_game *g);

/* game state */
int		init_game_state(t_game *g);
int		try_move(t_game *g, int dx, int dy);

/* utils */
int		put_error(const char *msg);

/* path finding (reachability validation) */
int		map_has_valid_path(t_game *g);

#endif
