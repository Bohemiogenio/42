/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 06:30:43 by raulsanc          #+#    #+#             */
/*   Updated: 2025/08/09 06:31:03 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_partial(char **m, int rows)
{
	int	i;

	if (!m)
		return ;
	i = 0;
	while (i < rows)
	{
		free(m[i]);
		i++;
	}
	free(m);
}

static char	*str_join_free(char *a, char *b, ssize_t blen)
{
	char	*res;
	size_t	alen;
	size_t	i;
	ssize_t	j;

	alen = 0;
	while (a && a[alen])
		alen++;
	res = (char *)malloc(alen + blen + 1);
	if (!res)
		return (free(a), NULL);
	i = 0;
	while (a && a[i])
	{
		res[i] = a[i];
		i++;
	}
	j = 0;
	while (j < blen)
	{
		res[i++] = b[j];
		j++;
	}
	res[i] = '\0';
	free(a);
	return (res);
}

static void	count_lines_and_width(char *s, int *lines, int *width)
{
	int	i;
	int	cur;

	*lines = 0;
	*width = 0;
	cur = 0;
	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\n')
		{
			if (cur > *width)
				*width = cur;
			cur = 0;
			(*lines)++;
		}
		else
			cur++;
		i++;
	}
	if (cur > 0)
	{
		if (cur > *width)
			*width = cur;
		(*lines)++;
	}
}

static char	*copy_line(char *s, int start, int end)
{
	int		len;
	int		k;
	char	*line;

	len = end - start;
	line = (char *)malloc(len + 1);
	if (!line)
		return (NULL);
	k = 0;
	while (k < len)
	{
		line[k] = s[start + k];
		k++;
	}
	line[len] = '\0';
	return (line);
}

static char	**split_lines(char *s, int *out_h, int *out_w)
{
	int		lines;
	int		w;
	int		i;
	int		start;
	int		row;
	char	**m;

	count_lines_and_width(s, &lines, &w);
	m = (char **)malloc(sizeof(char *) * (lines + 1));
	if (!m)
		return (NULL);
	i = 0;
	start = 0;
	row = 0;
	while (s && s[i])
	{
		if (s[i] == '\n')
		{
			m[row] = copy_line(s, start, i);
			if (!m[row])
				return (free_partial(m, row), NULL);
			row++;
			start = i + 1;
		}
		i++;
	}
	if (i > start)
	{
		m[row] = copy_line(s, start, i);
		if (!m[row])
			return (free_partial(m, row), NULL);
		row++;
	}
	m[row] = NULL;
	*out_h = lines;
	*out_w = w;
	return (m);
}

void	free_map(char **m)
{
	int	i;

	i = 0;
	if (!m)
		return ;
	while (m[i])
	{
		free(m[i]);
		i++;
	}
	free(m);
}

int	load_map(t_game *g, const char *path)
{
	int		fd;
	char	buf[1024];
	ssize_t	n;
	char	*all;

	all = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (write(2, "Error\ncannot open map\n", 22), 0);
	n = read(fd, buf, sizeof(buf));
	while (n > 0)
	{
		all = str_join_free(all, buf, n);
		if (!all)
			return (close(fd), write(2, "Error\nmalloc\n", 13), 0);
		n = read(fd, buf, sizeof(buf));
	}
	close(fd);
	if (!all || all[0] == '\0')
		return (write(2, "Error\nempty file\n", 17), 0);
	g->map = split_lines(all, &g->map_h, &g->map_w);
	free(all);
	if (!g->map)
		return (write(2, "Error\nsplit_lines\n", 18), 0);
	return (1);
}