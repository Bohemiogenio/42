/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 00:00:00 by rsanchez          #+#    #+#             */
/*   Updated: 2026/10/01 00:00:00 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Saca el nodo de arriba de la pila (el ultimo que se metio) */
static t_point	*pop_point(t_point **stack)
{
	t_point	*node;

	node = *stack;
	*stack = node->next;
	return (node);
}

/*
** Libera TODO lo que el flood fill tenia reservado (la matriz de
** visitados, el nodo que se estaba explorando ahora mismo y los
** nodos de pila que aun quedaran pendientes) y despues dispara el
** error. Lo hacemos asi, en vez de llamar a parse_error
** directamente, para no dejar memoria fugada justo en el momento
** en que detectamos que el MAPA tiene una fuga.
*/
static void	clean_and_error(t_flood_ctx *ctx, char *msg)
{
	t_point	*tmp;

	free_visited(ctx->visited, ctx->data->map.height);
	if (ctx->current)
		free(ctx->current);
	while (ctx->stack)
	{
		tmp = ctx->stack;
		ctx->stack = ctx->stack->next;
		free(tmp);
	}
	parse_error(ctx->data, msg);
}

/*
** Comprueba UNA casilla vecina (arriba, abajo, izquierda o derecha
** de la casilla actual) y decide que hacer:
** - si esta fuera del mapa, o la fila es mas corta de lo esperado,
**   o es un espacio/salto de linea -> el mapa tiene una fuga, error.
** - si es una pared ('1') -> no seguimos por ahi, pero no es error.
** - si ya la hemos visitado -> no hacemos nada, para no repetir.
** - si es suelo ('0' o una letra de jugador) y no visitada -> la
**   marcamos como visitada y la añadimos a la pila para explorarla.
*/
static void	process_neighbor(t_flood_ctx *ctx, int y, int x)
{
	char	c;
	t_point	*node;

	if (y < 0 || y >= ctx->data->map.height)
		clean_and_error(ctx, "map is not closed (reached map border)");
	if (x < 0 || (size_t)x >= ft_strlen(ctx->data->map.grid[y]))
		clean_and_error(ctx, "map is not closed (row too short)");
	c = ctx->data->map.grid[y][x];
	if (c == '1')
		return ;
	if (c == ' ' || c == '\n')
		clean_and_error(ctx, "map is not closed (open space found)");
	if (ctx->visited[y][x])
		return ;
	ctx->visited[y][x] = 1;
	node = new_point(y, x);
	if (!node)
		return ;
	node->next = ctx->stack;
	ctx->stack = node;
}

/*
** Funcion publica: comprueba que el mapa esta completamente
** rodeado de paredes, explorando desde la posicion del jugador
** hacia las 4 direcciones, casilla a casilla, sin usar recursion
** (usamos una pila manual para no arriesgarnos a un desbordamiento
** de pila con mapas muy grandes).
*/
void	check_map_closed(t_data *data)
{
	t_flood_ctx	ctx;
	t_point		*cur;

	ctx.data = data;
	ctx.visited = alloc_visited(&data->map);
	ctx.stack = new_point((int)data->player.y, (int)data->player.x);
	ctx.current = NULL;
	ctx.visited[(int)data->player.y][(int)data->player.x] = 1;
	while (ctx.stack)
	{
		cur = pop_point(&ctx.stack);
		ctx.current = cur;
		process_neighbor(&ctx, cur->y - 1, cur->x);
		process_neighbor(&ctx, cur->y + 1, cur->x);
		process_neighbor(&ctx, cur->y, cur->x - 1);
		process_neighbor(&ctx, cur->y, cur->x + 1);
		ctx.current = NULL;
		free(cur);
	}
	free_visited(ctx.visited, data->map.height);
}
