/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claherna <claherna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 00:00:00 by claherna          #+#    #+#             */
/*   Updated: 2026/03/01 21:27:31 by claherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_export(t_env *env)
{
	while (env)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env->key, STDOUT_FILENO);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(env->value, STDOUT_FILENO);
		ft_putendl_fd("\"", STDOUT_FILENO);
		env = env->next;
	}
}

static int	export_one(char *arg, t_shell *shell)
{
	char	*eq;
	char	*key;

	eq = ft_strchr(arg, '=');
	if (!eq)
	{
		if (!is_valid_identifier(arg))
		{
			print_error("export", arg, "not a valid identifier");
			return (1);
		}
		return (0);
	}
	key = ft_substr(arg, 0, eq - arg);
	if (!is_valid_identifier(key))
	{
		print_error("export", arg, "not a valid identifier");
		free(key);
		return (1);
	}
	env_set(&shell->env, key, eq + 1);
	free(key);
	return (0);
}

int	builtin_export(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	ret;

	if (!cmd->args[1])
	{
		print_export(shell->env);
		return (0);
	}
	ret = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (export_one(cmd->args[i], shell))
			ret = 1;
		i++;
	}
	return (ret);
}
