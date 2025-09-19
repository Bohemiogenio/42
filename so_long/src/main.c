/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <raulsanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 06:31:12 by raulsanc          #+#    #+#             */
/*   Updated: 2025/08/09 06:40:24 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* write string to given fd */
static void	putstr_fd(const char *s, int fd)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
}

/* check that filename ends with ".ber" */
static int	has_ext_ber(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	if (i < 4)
		return (0);
	return (s[i - 4] == '.' && s[i - 3] == 'b'
		&& s[i - 2] == 'e' && s[i - 1] == 'r');
}

/* clean shutdown */
int	on_close(t_game *g)
{
	destroy_textures(g);
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
	free_map(g->map);
	exit(0);
	return (0);
}

/* keyboard input handler */
int	on_key(int key, t_game *g)
{
	if (key == K_ESC)
		on_close(g);
	else if (key == K_W || key == K_UP)
		try_move(g, 0, -1);
	else if (key == K_S || key == K_DOWN)
		try_move(g, 0, 1);
	else if (key == K_A || key == K_LEFT)
		try_move(g, -1, 0);
	else if (key == K_D || key == K_RIGHT)
		try_move(g, 1, 0);
	return (0);
}

/* initialize mlx window */
int	game_init(t_game *g, int w, int h, char *title)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		return (put_error("mlx_init failed"));
	g->win = mlx_new_window(g->mlx, w, h, title);
	if (!g->win)
		return (put_error("mlx_new_window failed"));
	g->width = w;
	g->height = h;
	return (1);
}

int	main(int ac, char **av)
{
	t_game	g;

	/* IMPORTANT: zero-init everything (textures imgs start as NULL) */
	g = (t_game){0};

	if (ac != 2)
		return (write(2, "Usage: ./so_long maps/map.ber\n", 30), 1);
	if (!has_ext_ber(av[1]))
		return (put_error("map must have .ber extension"), 1);
	if (!load_map(&g, av[1]))
		return (1);
	if (!validate_map(&g))
		return (free_map(g.map), 1);
	if (!init_game_state(&g))
		return (free_map(g.map), 1);
	if (!game_init(&g, g.map_w * TILE, g.map_h * TILE, "so_long"))
		return (free_map(g.map), 1);
	if (!init_textures(&g))
		return (on_close(&g), 1);
	render_map(&g);
	putstr_fd("WASD / arrows to move. ESC to quit.\n", 1);
	mlx_hook(g.win, 17, 0, on_close, &g);
	mlx_key_hook(g.win, on_key, &g);
	mlx_loop(g.mlx);
	return (0);
}