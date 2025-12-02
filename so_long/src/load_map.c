/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:32:44 by raulsanc          #+#    #+#             */
/*   Updated: 2025/12/02 23:10:00 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Free a dynamically allocated map of given number of rows */
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

/* Count how many lines (rows) the map file has */
static int	count_rows(const char *path)
{
	int		fd;
	int		rows;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	rows = 0;
	line = get_next_line(fd);
	while (line)
	{
		rows++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (rows);
}

/* Allocate memory for the map matrix */
static char	**alloc_map(int rows)
{
	char	**map;

	map = malloc(sizeof(char *) * rows);
	if (!map)
		return (NULL);
	return (map);
}

/* Read map lines, trim newlines and fill the map array */
static int	fill_map_rows(int fd, t_game *g)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		g->map[i] = ft_strtrim(line, "\n");
		free(line);
		if (!g->map[i])
		{
			close(fd);
			return (0);
		}
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

/* Load the map from a file into the game structure */
int	load_map(const char *path, t_game *g)
{
	int	fd;

	g->rows = count_rows(path);
	if (g->rows <= 0)
		return (0);
	g->map = alloc_map(g->rows);
	if (!g->map)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	if (!fill_map_rows(fd, g))
		return (0);
	g->cols = ft_strlen(g->map[0]);
	return (1);
}
