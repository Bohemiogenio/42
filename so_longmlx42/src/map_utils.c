/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:34:57 by raulsanc          #+#    #+#             */
/*   Updated: 2025/11/03 14:57:14 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Count lines separated by newline; return 0 if s is NULL or empty */
size_t	sl_count_lines(const char *s)
{
	size_t	i;
	size_t	lines;

	if (!s || !*s)
		return (0);
	i = 0;
	lines = 1;
	while (s[i])
	{
		if (s[i] == '\n')
			lines++;
		i++;
	}
	return (lines);
}

/* Free first 'complete' lines and then the array itself */
void	sl_free_partial(char **out, size_t complete)
{
	size_t	i;

	i = 0;
	while (i < complete)
	{
		free(out[i]);
		i++;
	}
	free(out);
}

/* Malloc and copy [start, start+len) from src; NUL-terminated */
char	*sl_copy_line(const char *src, size_t start, size_t len)
{
	size_t	i;
	char	*destiny;

	destiny = (char *)malloc(len + 1);
	if (!destiny)
		return (NULL);
	i = 0;
	while (i < len)
	{
		destiny[i] = src[start + i];
		i++;
	}
	destiny[len] = '\0';
	return (destiny);
}