/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 00:00:00 by rsanchez          #+#    #+#             */
/*   Updated: 2026/10/02 00:00:00 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Una linea "en blanco" (solo espacios/tabs) se ignora en la config */
int	is_blank_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (line[i] == '\n' || line[i] == '\0');
}

/* Comprueba si "line" empieza por el identificador "id" + separador */
int	match_id(char *line, char *id)
{
	size_t	len;

	len = ft_strlen(id);
	if (ft_strncmp(line, id, len) != 0)
		return (0);
	return (line[len] == ' ' || line[len] == '\t');
}

/*
** Punto unico de error DENTRO del parseo de configuracion.
** Antes de llamar a parse_error, libera todas las lineas que
** todavia quedaban pendientes (incluida la que estaba fallando),
** para no dejar memoria fugada en un error a mitad de config.
*/
void	config_error(t_config_ctx *ctx, char *msg)
{
	t_lnode	*tmp;

	while (*ctx->lines)
	{
		tmp = *ctx->lines;
		*ctx->lines = tmp->next;
		free(tmp->line);
		free(tmp);
	}
	parse_error(ctx->data, msg);
}
