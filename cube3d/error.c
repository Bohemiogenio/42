/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 00:00:00 by rsanchez          #+#    #+#             */
/*   Updated: 2026/09/18 00:00:00 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Lee el archivo hasta el final para forzar que get_next_line
** libere su buffer interno, y despues cierra el fd.
** Evita dejar memoria reservada si morimos a mitad de lectura.
*/
static void	drain_fd(int fd)
{
	char	*tmp;

	if (fd < 0)
		return ;
	tmp = get_next_line(fd);
	while (tmp != NULL)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
	close(fd);
}

/*
** Punto unico de salida por error de parseo.
** Imprime "Error\n" + mensaje, limpia fd y memoria, y termina.
*/
void	parse_error(t_data *data, char *msg)
{
	printf("Error\n%s\n", msg);
	if (data)
	{
		drain_fd(data->fd);
		free_data(data);
	}
	exit(EXIT_FAILURE);
}
