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

/*
** Deja "data" en un estado seguro ANTES de poder fallar.
** Si no hacemos esto, un error muy temprano (p.ej. extension
** invalida) llamaria a parse_error con data->fd y los punteros
** del mapa sin inicializar: drain_fd podria leer de un fd que
** no es nuestro (hasta bloquearse leyendo de stdin) y free_map
** podria intentar liberar memoria basura.
*/
static void	init_data(t_data *data)
{
	data->fd = -1;
	data->map.grid = NULL;
	data->map.no_path = NULL;
	data->map.so_path = NULL;
	data->map.we_path = NULL;
	data->map.ea_path = NULL;
}

/* Valida la extension y abre el archivo, guardando el fd en data */
int	open_cub_file(char *filename, t_data *data)
{
	int	fd;

	init_data(data);
	if (!check_extension(filename))
		parse_error(data, "the file must have a .cub extension");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		parse_error(data, "could not open the map file");
	data->fd = fd;
	return (fd);
}
