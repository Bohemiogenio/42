/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 00:00:00 by rsanchez          #+#    #+#             */
/*   Updated: 2026/10/02 00:00:00 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Valida y convierte UN componente de color: solo digitos y
** entre 0 y 255 (maximo 3 digitos, asi ft_atoi nunca desborda).
** Devuelve -1 si no es valido (nunca un color real es negativo,
** asi que sirve como valor de error).
*/
static int	parse_component(char *s)
{
	int	i;

	if (!s || !s[0])
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		i++;
	}
	if (i > 3 || ft_atoi(s) > 255)
		return (-1);
	return (ft_atoi(s));
}

/* Libera un array de strings terminado en NULL (lo que crea ft_split) */
static void	free_parts(char **parts)
{
	int	i;

	i = 0;
	while (parts && parts[i])
		free(parts[i++]);
	free(parts);
}

/*
** Separa "r,g,b" en sus 3 componentes y los guarda en color[3].
** Libera "value" en cuanto deja de hacer falta, y libera "parts"
** en CUALQUIER camino de salida (exito o error) antes de seguir.
*/
static void	fill_color(t_config_ctx *ctx, char *value, int *color)
{
	char	**parts;
	int		i;
	int		v;

	parts = ft_split(value, ',');
	free(value);
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		free_parts(parts);
		config_error(ctx, "F/C line must have exactly 3 color values");
	}
	i = 0;
	while (i < 3)
	{
		v = parse_component(parts[i]);
		if (v < 0)
		{
			free_parts(parts);
			config_error(ctx, "invalid color value in F/C line");
		}
		color[i] = v;
		i++;
	}
	free_parts(parts);
}

/* Procesa la linea "F ..." (color del suelo), si no estaba ya puesta */
int	set_floor_color(t_config_ctx *ctx, char *line)
{
	char	*value;

	if (ctx->flags->f)
		config_error(ctx, "duplicate F line in config");
	value = ft_strtrim(line + 1, " \t\n");
	fill_color(ctx, value, ctx->data->map.floor_color);
	ctx->flags->f = 1;
	return (1);
}

/* Procesa la linea "C ..." (color del techo), si no estaba ya puesta */
int	set_ceiling_color(t_config_ctx *ctx, char *line)
{
	char	*value;

	if (ctx->flags->c)
		config_error(ctx, "duplicate C line in config");
	value = ft_strtrim(line + 1, " \t\n");
	fill_color(ctx, value, ctx->data->map.ceiling_color);
	ctx->flags->c = 1;
	return (1);
}
