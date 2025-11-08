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
	void	*mlx; /* MLX42 handler (mlx_t*) */
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

#endif
