/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 11:05:53 by raulsanc          #+#    #+#             */
/*   Updated: 2025/11/02 17:35:27 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include "MLX42/MLX42.h"

typedef struct s_game
{
	mlx_t	*mlx;
}	t_game;

void	sl_error(const char *msg);
int	sl_has_extension(const char *path, const char *ext);
void	sl_quit(t_game *g, int status);

/*HOOKS*/

void	sl_key_hook(mlx_key_data_t keydata, void *param);
void	sl_close_hook(void *param);

/* MAP */
char	**sl_read_map(const char *path);
void	sl_free_map(char **map);

/* TEMPORAL IMPRIME MAPA POR CONSOLA */
void	sl_print_map(char **map);

#endif
