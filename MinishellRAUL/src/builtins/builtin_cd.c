/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claherna <claherna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 00:00:00 by claherna          #+#    #+#             */
/*   Updated: 2026/03/06 20:03:02 by claherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_or_err(t_shell *shell, char *key, char *msg)
{
	char	*val;

	val = env_get(shell->env, key);
	if (!val)
		print_error("cd", NULL, msg);
	return (val);
}

static char	*get_cd_path(t_cmd *cmd, t_shell *shell)
{
	if (!cmd->args[1])
		return (get_env_or_err(shell, "HOME", "HOME not set"));
	if (ft_strncmp(cmd->args[1], "-", 2) == 0)
		return (get_env_or_err(shell, "OLDPWD", "OLDPWD not set"));
	return (cmd->args[1]);
}

static void	update_pwd(t_shell *shell, char *pwd)
{
	char	cwd[4096];

	if (pwd)
		env_set(&shell->env, "OLDPWD", pwd);
	if (getcwd(cwd, sizeof(cwd)))
		env_set(&shell->env, "PWD", cwd);
}

int	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	char	old[4096];
	char	*p;

	if (cmd->args[1] && cmd->args[2])
		return (print_error("cd", NULL, "too many arguments"), 1);
	p = get_cd_path(cmd, shell);
	if (!p)
		return (1);
	if (!getcwd(old, sizeof(old)))
		old[0] = '\0';
	if (chdir(p) == -1)
		return (print_error("cd", p, strerror(errno)), 1);
	if (cmd->args[1] && ft_strncmp(cmd->args[1], "-", 2) == 0)
		ft_putendl_fd(p, STDOUT_FILENO);
	update_pwd(shell, old);
	return (0);
}
