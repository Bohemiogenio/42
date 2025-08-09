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

/* Libera mapa parcial si falla malloc en split_lines */
static void	free_partial(char **m, int rows)
{
	int i;

	if (!m)
		return;
	i = 0;
	while (i < rows)
	{
		free(m[i]);
		i++;
	}
	free(m);
}

/* Concatena dos buffers a (malloc) + b (buffer), liberando a */
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
	{
		free(a);
		return (NULL);
	}
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

/* Divide el string completo en líneas y devuelve char** terminado en NULL */
static char	**split_lines(char *s, int *out_h, int *out_w)
{
	int		lines;
	int		w;
	int		cur;
	int		i;
	int		row;
	int		start;
	int		len;
	int		k;
	char	**m;

	lines = 0;
	w = 0;
	cur = 0;
	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\n')
		{
			if (cur > w)
				w = cur;
			cur = 0;
			lines++;
		}
		else
			cur++;
		i++;
	}
	/* ✅ Solo añade línea si quedó texto sin \n al final */
	if (cur > 0)
	{
		if (cur > w)
			w = cur;
		lines++;
	}
	m = (char **)malloc(sizeof(char *) * (lines + 1));
	if (!m)
		return (NULL);
	row = 0;
	start = 0;
	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\n')
		{
			len = i - start;
			m[row] = (char *)malloc(len + 1);
			if (!m[row])
				return (free_partial(m, row), NULL);
			k = 0;
			while (k < len)
			{
				m[row][k] = s[start + k];
				k++;
			}
			m[row][len] = '\0';
			row++;
			start = i + 1;
		}
		i++;
	}
	/* Última línea solo si había cola sin \n (cur > 0) */
	if (cur > 0)
	{
		len = i - start;
		m[row] = (char *)malloc(len + 1);
		if (!m[row])
			return (free_partial(m, row), NULL);
		k = 0;
		while (k < len)
		{
			m[row][k] = s[start + k];
			k++;
		}
		m[row][len] = '\0';
		row++;
	}
	m[row] = NULL;
	*out_h = lines;
	*out_w = w;
	return (m);
}

/* Libera un mapa completo */
void	free_map(char **m)
{
	int i;

	i = 0;
	if (!m)
		return;
	while (m[i])
	{
		free(m[i]);
		i++;
	}
	free(m);
}

/* Lee un archivo de mapa y lo carga en g->map */
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
		{
			close(fd);
			return (write(2, "Error\nmalloc\n", 13), 0);
		}
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
