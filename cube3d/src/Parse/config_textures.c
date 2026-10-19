/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 00:00:00 by rsanchez          #+#    #+#             */
/*   Updated: 2026/10/02 00:00:00 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static char	*extract_path(t_config_ctx *ctx, char *line, int id_len)
{
	char	*path;
	int		fd;

	path = ft_strtrim(line + id_len, " \t\n");
	if (!path || !path[0])
	{
		free(path);
		config_error(ctx, "missing texture path in config line");
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(path);
		config_error(ctx, "texture file could not be opened");
	}
	close(fd);
	return (path);
}

int	set_no(t_config_ctx *ctx, char *line)
{
	if (ctx->flags->no)
		config_error(ctx, "duplicate NO line in config");
	ctx->data->map.images.paths[NORTH] = extract_path(ctx, line, 2);
	ctx->flags->no = 1;
	return (1);
}

int	set_so(t_config_ctx *ctx, char *line)
{
	if (ctx->flags->so)
		config_error(ctx, "duplicate SO line in config");
	ctx->data->map.images.paths[SOUTH] = extract_path(ctx, line, 2);
	ctx->flags->so = 1;
	return (1);
}

int	set_we(t_config_ctx *ctx, char *line)
{
	if (ctx->flags->we)
		config_error(ctx, "duplicate WE line in config");
	ctx->data->map.images.paths[WEST] = extract_path(ctx, line, 2);
	ctx->flags->we = 1;
	return (1);
}

int	set_ea(t_config_ctx *ctx, char *line)
{
	if (ctx->flags->ea)
		config_error(ctx, "duplicate EA line in config");
	ctx->data->map.images.paths[EAST] = extract_path(ctx, line, 2);
	ctx->flags->ea = 1;
	return (1);
}
