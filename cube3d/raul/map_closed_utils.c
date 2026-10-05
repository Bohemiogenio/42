/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closed_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 00:00:00 by rsanchez          #+#    #+#             */
/*   Updated: 2026/10/01 00:00:00 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Reserva una matriz de enteros del mismo tamaño que el mapa
** (height filas x width columnas), inicializada a 0.
** La usamos para marcar que casillas ya ha visitado el flood fill,
** y asi no procesar la misma casilla dos veces ni entrar en un
** bucle infinito.
*/
int	**alloc_visited(t_map *map)
{
	int	**visited;
	int	i;
	int	j;

	visited = malloc(sizeof(int *) * map->height);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		visited[i] = malloc(sizeof(int) * (map->width + 1));
		j = 0;
		while (visited[i] && j <= map->width)
		{
			visited[i][j] = 0;
			j++;
		}
		i++;
	}
	return (visited);
}

/* Libera la matriz de visitados, fila a fila y despues el array */
void	free_visited(int **visited, int height)
{
	int	i;

	if (!visited)
		return ;
	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

/*
** Crea un nodo suelto de la pila con una coordenada (y, x).
** Lo usa el flood fill cada vez que descubre una casilla nueva
** que todavia tiene que explorar.
*/
t_point	*new_point(int y, int x)
{
	t_point	*node;

	node = malloc(sizeof(t_point));
	if (!node)
		return (NULL);
	node->y = y;
	node->x = x;
	node->next = NULL;
	return (node);
}
