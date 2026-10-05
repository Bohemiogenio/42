/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 00:00:00 by rsanchez          #+#    #+#             */
/*   Updated: 2026/10/02 00:00:00 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Decide que es esta linea y la procesa si es de configuracion.
** Devuelve 1 si la linea era config (o en blanco, se ignora) y
** hay que seguir leyendo; 0 si la linea es ya el mapa.
*/
static int	process_config_line(t_config_ctx *ctx, char *line)
{
	if (is_blank_line(line))
		return (1);
	if (match_id(line, "NO"))
		return (set_no(ctx, line));
	if (match_id(line, "SO"))
		return (set_so(ctx, line));
	if (match_id(line, "WE"))
		return (set_we(ctx, line));
	if (match_id(line, "EA"))
		return (set_ea(ctx, line));
	if (match_id(line, "F"))
		return (set_floor_color(ctx, line));
	if (match_id(line, "C"))
		return (set_ceiling_color(ctx, line));
	return (0);
}

/* Comprueba que las 6 lineas de configuracion han aparecido */
static void	check_flags_complete(t_config_ctx *ctx)
{
	if (!ctx->flags->no || !ctx->flags->so || !ctx->flags->we
		|| !ctx->flags->ea)
		config_error(ctx, "missing NO/SO/WE/EA texture line(s)");
	if (!ctx->flags->f || !ctx->flags->c)
		config_error(ctx, "missing F or C color line(s)");
}

/* Pone a 0 los 6 marcadores de "linea de config ya vista" */
static void	init_flags(t_config_flags *flags)
{
	flags->no = 0;
	flags->so = 0;
	flags->we = 0;
	flags->ea = 0;
	flags->f = 0;
	flags->c = 0;
}

/*
** Funcion publica: lee todo el archivo, consume las lineas de
** configuracion (rellenando t_map con texturas y colores) y deja
** en fill_map_grid el resto de lineas, que ya son el mapa.
*/
void	parse_config(t_data *data)
{
	t_lnode			*lines;
	t_lnode			*tmp;
	t_config_flags	flags;
	t_config_ctx	ctx;

	init_flags(&flags);
	lines = read_all_lines(data->fd);
	close(data->fd);
	data->fd = -1;
	ctx.data = data;
	ctx.flags = &flags;
	ctx.lines = &lines;
	while (lines && process_config_line(&ctx, lines->line))
	{
		tmp = lines;
		lines = lines->next;
		free(tmp->line);
		free(tmp);
	}
	check_flags_complete(&ctx);
	fill_map_grid(data, lines);
}
