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

#include "../../include/cub3D.h"

static t_point	*pop_point(t_point **stack)
{
	t_point	*node;

	node = *stack;
	*stack = node->next;
	return (node);
}

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
