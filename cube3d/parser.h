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

typedef struct s_lnode
{
	char			*line;
	struct s_lnode	*next;
}	t_lnode;

int		ft_arr_len(char **arr);
void	ft_free_split(char **arr);
int		ft_atoi_strict(const char *s, int *out);
void	parse_error(t_data *data, char *msg);
int		check_extension(char *filename);
int		open_cub_file(char *filename, t_data *data);
int		parse_config_line(char *line, t_data *data);
int		is_config_line(char *line);
int		all_config_filled(t_map *map);
int		parse_map(char *filename, t_data *data);
void	free_map(t_map *map);
void	free_data(t_data *data);
int		fill_map_grid(t_data *data);

#endif
