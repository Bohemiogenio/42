/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:17:05 by raulsanc          #+#    #+#             */
/*   Updated: 2025/11/10 13:17:45 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# include "../libft/libft.h"
# include "../gnl/get_next_line.h"

typedef struct s_game
{
	char	**map;
	int		rows;
	int		cols;
	void	*mlx;
	void	*img_floor;
	void	*img_wall;
}	t_game;

/* load_map.c */
int		load_map(const char *path, t_game *g);
int		has_ber_extension(const char *path);
void	free_map(char **map, int rows);

/* validaciones */
int		is_rectangular(t_game *g);
int		validate_charset_counts(t_game *g);
int		is_closed_by_walls(t_game *g);
int		validate_path(t_game *g);

/* init_mlx42.c */
int		game_open_window(t_game *g);
int		game_loop(t_game *g);

/* render_basic */
int		render_basic_init(t_game *g);
int		render_basit_draw(t_game *g);

#endif
