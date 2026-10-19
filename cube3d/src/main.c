/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmorente <mmorente@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 16:24:06 by mmorente          #+#    #+#             */
/*   Updated: 2026/09/28 12:47:02 by mmorente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
	{
		ft_printf("Error\nusage: ./cub3D <map.cub>\n");
		return (1);
	}
	ft_bzero(&data, sizeof(t_data));
	ft_bzero(&data.keys, sizeof(t_keys));
	parse_map(argv[1], &data);
	game(&data);
	return (0);
}
