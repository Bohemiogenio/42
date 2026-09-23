/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 00:00:00 by rsanchez          #+#    #+#             */
/*   Updated: 2026/09/22 00:00:00 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_lnode	*new_lnode(char *line)
{
	t_lnode	*node;

	node = malloc(sizeof(t_lnode));
	if (!node)
		return (NULL);
	node->line = line;
	node->next = NULL;
	return (node);
}

static void	push_lnode(t_lnode **head, t_lnode **tail, char *line)
{
	t_lnode	*node;

	node = new_lnode(line);
	if (!node)
		return ;
	if (!*head)
		*head = node;
	else
		(*tail)->next = node;
	*tail = node;
}

static char	**lnode_list_to_grid(t_lnode *head, int len)
{
	char	**grid;
	t_lnode	*tmp;
	int		i;

	grid = malloc(sizeof(char *) * (len + 1));
	if (!grid)
		return (NULL);
	i = 0;
	while (head)
	{
		grid[i] = head->line;
		tmp = head;
		head = head->next;
		free(tmp);
		i++;
	}
	grid[i] = NULL;
	return (grid);
}

int	fill_map_grid(t_data *data)
{
	t_lnode	*head;
	t_lnode	*tail;
	char	*line;
	int		len;

	head = NULL;
	tail = NULL;
	len = 0;
	line = get_next_line(data->fd);
	while (line)
	{
		push_lnode(&head, &tail, line);
		len++;
		line = get_next_line(data->fd);
	}
	if (len == 0)
		parse_error(data, "no map content found in the file");
	data->map.grid = lnode_list_to_grid(head, len);
	data->map.height = len;
	return (0);
}