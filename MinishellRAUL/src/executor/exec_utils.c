/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claherna <claherna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 00:00:00 by claherna          #+#    #+#             */
/*   Updated: 2026/03/01 21:31:26 by claherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_fds(t_shell *shell)
{
	dup2(shell->stdin_backup, STDIN_FILENO);
	dup2(shell->stdout_backup, STDOUT_FILENO);
}

void	setup_child_fds(t_cmd *cmd, int in_fd, int *pipefd)
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (cmd->next && pipefd)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
}

void	exec_child_cmd(t_cmd *cmd, t_shell *shell)
{
	char	**envp;
	char	*path;

	if (!cmd || !cmd->args || !cmd->args[0])
		exit(0);
	if (is_builtin(cmd->args[0]))
		exit(exec_builtin(cmd, shell));
	path = find_command_path(cmd->args[0], shell->env);
	if (!path)
	{
		print_error(cmd->args[0], NULL, "command not found");
		exit(127);
	}
	envp = env_to_array(shell->env);
	execve(path, cmd->args, envp);
	print_error(cmd->args[0], NULL, strerror(errno));
	free(path);
	free_array(envp);
	exit(126);
}
