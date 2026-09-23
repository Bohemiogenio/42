/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 00:00:00 by rsanchez          #+#    #+#             */
/*   Updated: 2026/09/18 00:00:00 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Comprueba que el nombre de archivo termina en ".cub" */
int	check_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

/* Valida la extension y abre el archivo, guardando el fd en data */
int	open_cub_file(char *filename, t_data *data)
{
	int	fd;

	if (!check_extension(filename))
		parse_error(data, "the file must have a .cub extension");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		parse_error(data, "could not open the map file");
	data->fd = fd;
	return (fd);
}
