/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorente <mmorente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:20:13 by mmorente          #+#    #+#             */
/*   Updated: 2026/09/16 12:30:15 by mmorente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*delete_line_read(char *backup)
{
	int		i;
	int		rest_i;
	char	*rest;

	i = 0;
	while (backup[i] && (backup[i] != '\n'))
		i++;
	if (!backup[i])
	{
		free(backup);
		return (NULL);
	}
	rest = malloc(sizeof(char) * (ft_strlen_gnl(backup) - i + 1));
	if (!rest)
	{
		free(rest);
		return (NULL);
	}
	++i;
	rest_i = 0;
	while (backup[i])
		rest[rest_i++] = backup[i++];
	rest[rest_i] = '\0';
	free(backup);
	return (rest);
}

char	*pass_line(char *backup)
{
	int		i;
	char	*line;

	i = 0;
	if (backup[0] == 0)
		return (NULL);
	while (backup[i] && (backup[i] != '\n'))
		i++;
	line = ft_calloc(sizeof(char), (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (backup[i] && (backup[i] != '\n'))
	{
		line[i] = backup[i];
		i++;
	}
	if (backup[i] == '\n')
	{
		line[i] = backup[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*read_fd(char *result, int fd)
{
	int		byte_read;
	char	*buffer;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	if (!result)
		result = ft_calloc(1, 1);
	byte_read = 1;
	while (byte_read != 0 && !(ft_strchr_gnl(result, '\n')))
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < 0)
		{
			free(buffer);
			free(result);
			return (NULL);
		}
		buffer[byte_read] = '\0';
		result = ft_strjoin_gnl(result, buffer);
	}
	free(buffer);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line_result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_fd(buffer, fd);
	if (!buffer)
		return (NULL);
	line_result = pass_line(buffer);
	buffer = delete_line_read(buffer);
	return (line_result);
}
