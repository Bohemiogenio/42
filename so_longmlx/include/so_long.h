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
	int	rows;
	int	cols;
}	t_game;

/* map_read.c */
int	load_map(const char *path, t_game *g);
int	has_ber_extension(const char *path);
void	free_map(char **map, int rows);º

#endif

