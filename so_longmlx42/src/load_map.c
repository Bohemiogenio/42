/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:39:43 by raulsanc          #+#    #+#             */
/*   Updated: 2025/11/08 13:20:54 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Delete \n ,for nice strlen */
static void	trim_newline(char *s)
{
	size_t	i;

	if (!s)
		return ;
	i = ft_strlen(s);
	if (i == 0)
		return ;
	if (s[i - 1] == '\n')
		s[i - 1] = '\0';
}

/* Free map memory */
void	free_map(char **map, int rows)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

/* Add a new line to the map */
static char	**add_line(char **old, int old_rows, char *line)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (old_rows + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < old_rows)
	{
		new_map[i] = old[i];
		i++;
	}
	new_map[old_rows] = line;
	free(old);
	return (new_map);
}

/* Read all lines from fd and store in game map */
static int	read_lines(int fd, t_game *g)
{
	char	*line;
	char	**tmp;

	line = get_next_line(fd);
	while (line)
	{
		trim_newline(line);
		tmp = add_line(g->map, g->rows, line);
		if (!tmp)
		{
			free(line);
			free_map(g->map, g->rows);
			return (1);
		}
		g->map = tmp;
		g->rows++;
		line = get_next_line(fd);
	}
	return (0);
}

/* Load map from .ber file into game structure */
int	load_map(const char *path, t_game *g)
{
	int	fd;

	g->map = NULL;
	g->rows = 0;
	g->cols = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	if (read_lines(fd, g) != 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	if (g->rows == 0)
		return (1);
	g->cols = (int)ft_strlen(g->map[0]);
	return (0);
}
