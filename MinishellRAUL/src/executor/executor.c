/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claherna <claherna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 00:00:00 by claherna          #+#    #+#             */
/*   Updated: 2026/03/01 21:27:31 by claherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_count(t_cmd *cmds)
{
	int	count;

	count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}

static int	exec_single_builtin(t_cmd *cmd, t_shell *shell)
{
	int	ret;

	if (apply_redirections(cmd, shell) == -1)
		return (1);
	ret = exec_builtin(cmd, shell);
	restore_fds(shell);
	return (ret);
}

static int	wait_children(pid_t last_pid, int count)
{
	int		status;
	int		last_status;
	int		i;
	pid_t	pid;

	i = 0;
	last_status = 0;
	while (i < count)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (last_status);
}

int	executor(t_cmd *cmds, t_shell *shell)
{
	int		count;
	pid_t	last_pid;

	if (!cmds || !cmds->args)
		return (0);
	if (!cmds->args[0] && !cmds->redirs && !cmds->next)
		return (0);
	count = cmd_count(cmds);
	if (count == 1 && is_builtin(cmds->args[0]))
		return (exec_single_builtin(cmds, shell));
	last_pid = exec_pipeline(cmds, shell);
	if (last_pid < 0)
		return (1);
	return (wait_children(last_pid, count));
}
