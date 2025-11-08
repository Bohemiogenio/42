/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:53:25 by raulsanc          #+#    #+#             */
/*   Updated: 2025/11/08 17:53:32 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	print_usage(const char *prog)
{
	write(2, "Uso: ", 5);
	write(2, prog, (int)ft_strlen(prog));
	write(2, " ruta_al_mapa.ber\n", 18);
}

static int	fail(const char *msg, t_game *g)
{
	write(2, msg, (int)ft_strlen(msg));
	if (g && g->map)
		free_map(g->map, g->rows);
	return (1);
}

int	main(int ac, char **av)
{
	t_game	g;

	if (ac != 2)
		return (print_usage(av[0]), 1);
	if (!has_ber_extension(av[1]))
		return (fail("ERROR: extension .ber\n", NULL));
	if (load_map(av[1], &g) != 0)
		return (fail("ERROR: lectura mapa\n", NULL));
	if (!is_rectangular(&g))
		return (fail("ERROR: no rectangular\n", &g));
	if (!validate_charset_counts(&g))
		return (fail("ERROR: charset/C/E/P\n", &g));
	if (!is_closed_by_walls(&g))
		return (fail("ERROR: paredes\n", &g));
	if (!validate_path(&g))
		return (fail("ERROR: camino inaccesible\n", &g));
	if (game_open_window(&g) != 0)
		return (fail("ERROR: mlx42\n", &g));
	return (game_loop(&g));
}
