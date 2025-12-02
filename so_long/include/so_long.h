/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:17:05 by raulsanc          #+#    #+#             */
/*   Updated: 2025/12/03 00:10:00 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <MLX42/MLX42.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"

# define TILE_SIZE 64

typedef struct s_game
{
	char			**map;
	int				rows;
	int				cols;
	mlx_t			*mlx;
	mlx_texture_t	*tx_floor;
	mlx_texture_t	*tx_wall;
	mlx_texture_t	*tx_player;
	mlx_texture_t	*tx_collect;
	mlx_texture_t	*tx_exit;
	mlx_image_t		*img_floor;
	mlx_image_t		*img_wall;
	mlx_image_t		*img_player;
	mlx_image_t		*img_collect;
	mlx_image_t		*img_exit;
	int				player_x;
	int				player_y;
	int				total_collect;
	int				collected;
	int				moves;
}	t_game;

typedef struct s_bfs
{
	int	qx[10000];
	int	qy[10000];
	int	start;
	int	end;
}	t_bfs;

int		load_map(const char *path, t_game *g);
void	free_map(char **map, int rows);

int		has_ber_extension(const char *path);

int		is_rectangular(t_game *g);
int		validate_charset_counts(t_game *g);
int		is_closed_by_walls(t_game *g);
int		validate_path(t_game *g);

void	queue_push(t_bfs *b, int x, int y);

int		game_open_window(t_game *g);

void	render_map(t_game *g);
int		render_sprites_init(t_game *g);

void	handle_input(mlx_key_data_t keydata, void *param);

void	exit_error(t_game *g, const char *msg);
void	free_all(t_game *g);
void	print_moves(t_game *g);

#endif
