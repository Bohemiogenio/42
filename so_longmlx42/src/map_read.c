/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 14:59:07 by raulsanc          #+#    #+#             */
/*   Updated: 2025/11/02 17:35:21 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

static char	*sl_read_all(const char *path, size_t *out_len)
{
	int	fd;
	struct stat st;
	ssize_t	nread;
	size_t	to:wread;
	size_t	pos;
	char	*buf;

	if (stat(path, &st) == -1 || st.st_size < 0)
		return (NULL);
	toread = (size_t)st.st_size;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);

	buf = malloc(sizeof(char) * (toread + 1));
	if (!buf)
		return (close(fd), NULL);
	pos = 0;
	while(pos < toread)
	{
		nread = read(fd, buf + pos, toread - pos);
		if (nread <= 0)
			break ;
		pos += (size_t)nread;
	}
	close(fd);
	if (pos != toread)
		return (free(buf), NULL);
	buf[pos] = '\0';
	if (out_len)
		*out_len = pos;
	return (buf);
}
