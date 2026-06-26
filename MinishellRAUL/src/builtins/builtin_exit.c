/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claherna <claherna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 00:00:00 by claherna          #+#    #+#             */
/*   Updated: 2026/03/01 21:30:25 by claherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_cmd *cmd, t_shell *shell)
{
	int	exit_code;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (!cmd->args[1])
	{
		exit_code = shell->exit_status;
		free_shell(shell);
		exit(exit_code);
	}
	if (!is_numeric(cmd->args[1]))
	{
		print_error("exit", cmd->args[1], "numeric argument required");
		free_shell(shell);
		exit(2);
	}
	if (cmd->args[2])
	{
		print_error("exit", NULL, "too many arguments");
		return (1);
	}
	exit_code = (unsigned char)ft_atoi(cmd->args[1]);
	free_shell(shell);
	exit(exit_code);
	return (0);
}
