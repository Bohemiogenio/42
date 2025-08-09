#include "so_long.h"

/* copia nearest-neighbor de src -> dst (ambas ARGB32) escalando a TILE×TILE */
static int	scale_to_tile(void *mlx, t_img *dst, t_img *src)
{
	char	*sd; char *dd;
	int		sbpp, slen, send;
	int		dbpp, dlen, dend;
	int		y, x;
	int		sx, sy;
	int		*spx; int *dpx;

	dst->img = mlx_new_image(mlx, TILE, TILE);
	if (!dst->img)
		return (put_error("mlx_new_image failed"));
	dd = mlx_get_data_addr(dst->img, &dbpp, &dlen, &dend);
	sd = mlx_get_data_addr(src->img, &sbpp, &slen, &send);
	if (!dd || !sd || dbpp != 32 || sbpp != 32)
		return (put_error("bpp != 32 (X11)"));
	for (y = 0; y < TILE; y++)
	{
		sy = (y * src->h) / TILE;
		for (x = 0; x < TILE; x++)
		{
			sx = (x * src->w) / TILE;
			spx = (int *)(sd + sy * slen + sx * 4);
			dpx = (int *)(dd + y * dlen + x * 4);
			*dpx = *spx;
		}
	}
	dst->w = TILE;
	dst->h = TILE;
	return (1);
}

/* carga un .xpm de cualquier tamaño y lo deja en TILE×TILE */
static int	load_xpm_scaled(t_game *g, t_img *dst, const char *path)
{
	t_img src;

	src.img = mlx_xpm_file_to_image(g->mlx, (char *)path, &src.w, &src.h);
	if (!src.img)
		return (put_error("mlx_xpm_file_to_image failed"));
	if (!scale_to_tile(g->mlx, dst, &src))
		return (mlx_destroy_image(g->mlx, src.img), 0);
	mlx_destroy_image(g->mlx, src.img);
	return (1);
}

int	init_textures(t_game *g)
{
	if (!load_xpm_scaled(g, &g->tx.floor_, "assets/floor.xpm")) return (0);
	if (!load_xpm_scaled(g, &g->tx.wall,   "assets/wall.xpm"))  return (0);
	if (!load_xpm_scaled(g, &g->tx.player, "assets/player.xpm"))return (0);
	if (!load_xpm_scaled(g, &g->tx.exit,   "assets/exit.xpm"))  return (0);
	if (!load_xpm_scaled(g, &g->tx.coin,   "assets/coin.xpm"))  return (0);
	return (1);
}

void	destroy_textures(t_game *g)
{
	if (!g->mlx) return;
	if (g->tx.floor_.img) mlx_destroy_image(g->mlx, g->tx.floor_.img);
	if (g->tx.wall.img)   mlx_destroy_image(g->mlx, g->tx.wall.img);
	if (g->tx.player.img) mlx_destroy_image(g->mlx, g->tx.player.img);
	if (g->tx.exit.img)   mlx_destroy_image(g->mlx, g->tx.exit.img);
	if (g->tx.coin.img)   mlx_destroy_image(g->mlx, g->tx.coin.img);
}

static void	put_tile(t_game *g, t_img *tex, int x, int y)
{
	mlx_put_image_to_window(g->mlx, g->win, tex->img, x * TILE, y * TILE);
}

void	render_map(t_game *g)
{
	for (int y = 0; y < g->map_h; y++)
	for (int x = 0; x < g->map_w; x++)
	{
		char c = g->map[y][x];
		put_tile(g, &g->tx.floor_, x, y);
		if (c == '1') put_tile(g, &g->tx.wall, x, y);
		else if (c == 'P') put_tile(g, &g->tx.player, x, y);
		else if (c == 'E') put_tile(g, &g->tx.exit, x, y);
		else if (c == 'C') put_tile(g, &g->tx.coin, x, y);
	}
}
