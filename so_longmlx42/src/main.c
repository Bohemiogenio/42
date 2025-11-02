#include "so_long.h"

/* Initialize game, check arguments, init MLX42, register hooks and exit cleanly */
int main(int ac, char **av)
{
	t_game g;

	g.mlx = NULL;

	if (ac != 2 || !sl_has_extension(av[1], ".ber"))
	{
		sl_error("Usage: ./so_long <map_file.ber>");
		sl_quit(&g, 1);
	}
	
	g.mlx = mlx_init(640, 480, "so_long", false);
	if (!g.mlx)
	{
		sl_error("Failed to initialize MLX42");
		sl_quit(&g, 1);

	}
	
	mlx_key_hook(g.mlx, &sl_key_hook, &g);
	mlx_close_hook(g.mlx, &sl_close_hook, &g);
	mlx_loop(g.mlx);
	sl_quit(&g, 0);
}
