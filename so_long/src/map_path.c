#include "so_long.h"

static char **dup_map(char **m, int h)
{
    char **cpy = (char **)malloc((h + 1) * sizeof(char *));
    if (!cpy) return NULL;
    for (int y = 0; y < h; ++y) {
        size_t len = strlen(m[y]);
        cpy[y] = (char *)malloc(len + 1);
        if (!cpy[y]) { /* free parcial */
            for (int j = 0; j < y; ++j) free(cpy[j]);
            free(cpy);
            return NULL;
        }
        memcpy(cpy[y], m[y], len + 1);
    }
    cpy[h] = NULL;
    return cpy;
}

static void free_m(char **m)
{
    if (!m) return;
    for (int i = 0; m[i]; ++i) free(m[i]);
    free(m);
}

/* BFS sencillo en una copia del mapa */
int map_has_valid_path(t_game *g)
{
    int w = g->map_w, h = g->map_h;
    char **mm = dup_map(g->map, h);
    if (!mm) return 0;

    /* localizar P */
    int sx = -1, sy = -1;
    for (int y=0; y<h; ++y)
        for (int x=0; x<w; ++x)
            if (mm[y][x] == 'P') { sx=x; sy=y; }

    if (sx < 0) { free_m(mm); return 0; }

    /* cola para BFS */
    int cap = w*h;
    int *qx = (int*)malloc(cap*sizeof(int));
    int *qy = (int*)malloc(cap*sizeof(int));
    int qb=0, qe=0;
    if (!qx || !qy) { free(qx); free(qy); free_m(mm); return 0; }

    /* contadores objetivo */
    int need_lamps = 0;
    int exit_reachable = 0;
    for (int y=0; y<h; ++y)
        for (int x=0; x<w; ++x)
            if (mm[y][x] == 'L' || mm[y][x] == 'C') /* por si usas 'C' */
                need_lamps++;

    qx[qe]=sx; qy[qe]=sy; qe++;
    mm[sy][sx] = 'V'; /* visitado */

    while (qb < qe) {
        int x = qx[qb], y = qy[qb]; qb++;

        const int dx[4] = {1,-1,0,0};
        const int dy[4] = {0,0,1,-1};
        for (int k=0; k<4; ++k) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx<0 || ny<0 || nx>=w || ny>=h) continue;
            char c = mm[ny][nx];
            if (c == '1' || c == 'V') continue; /* pared o ya visto */

            if (c == 'L' || c == 'C') need_lamps--;
            if (c == 'E') exit_reachable = 1;

            mm[ny][nx] = 'V';
            qx[qe]=nx; qy[qe]=ny; qe++;
        }
    }

    free(qx); free(qy); free_m(mm);

    /* válido si todas las lámparas son alcanzables y la salida también */
    return (need_lamps == 0 && exit_reachable);
}
