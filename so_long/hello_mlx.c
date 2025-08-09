#include "mlx.h"
#include <stdlib.h>
#include <unistd.h>

int on_destroy(void *p) { (void)p; exit(0); return 0; }
int on_key(int keycode, void *p) { (void)p; if (keycode == 65307) exit(0); return 0; }

int main(void)
{
    void *mlx = mlx_init();
    void *win;

    if (!mlx) { write(2, "Error\nmlx_init failed\n", 22); return 1; }
    win = mlx_new_window(mlx, 640, 480, "Hello MLX");
    if (!win) { write(2, "Error\nmlx_new_window failed\n", 28); return 1; }

    mlx_hook(win, 17, 0, on_destroy, 0);
    mlx_key_hook(win, on_key, 0);
    mlx_loop(mlx);
    return 0;
}

