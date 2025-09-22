/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raulsanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:23:14 by raulsanc          #+#    #+#             */
/*   Updated: 2025/02/09 11:25:08 by raulsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef RUSH01_H
# define RUSH01_H

# include <unistd.h>
# include <stdlib.h>

# define SIZE 4

void	ft_putstr(char *str);
void	print_grid(int grid[SIZE][SIZE]);
void	ft_init_grid(int grid[SIZE][SIZE]);
int		validate_input(char *str, int clues[SIZE *4]);
int		solve(int grid[SIZE][SIZE], int clues[SIZE *4], int row, int col);
int		check_visibility(int grid[SIZE][SIZE], int clues[SIZE *4]);

#endif
