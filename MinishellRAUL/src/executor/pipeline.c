/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claherna <claherna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 00:00:00 by claherna          #+#    #+#             */
/*   Updated: 2026/03/01 21:31:12 by claherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(t_cmd *cmd, t_shell *shell, int in_fd, int *pipefd)
{
	setup_signals_child();
	setup_child_fds(cmd, in_fd, pipefd);
	if (apply_redirections(cmd, shell) == -1)
		exit(1);
	exec_child_cmd(cmd, shell);
}

static void	close_pipe_fds(int in_fd, int *pipefd, t_cmd *cmd)
{
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (cmd->next && pipefd)
		close(pipefd[1]);
}

static pid_t	fork_and_exec(t_cmd *cmd, t_shell *sh, int in_fd, int *pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		child_process(cmd, sh, in_fd, pipefd);
	close_pipe_fds(in_fd, pipefd, cmd);
	return (pid);
}

pid_t	exec_pipeline(t_cmd *cmds, t_shell *shell)
{
	int		pipefd[2];
	int		in_fd;
	pid_t	pid;
	t_cmd	*cmd;

	in_fd = STDIN_FILENO;
	cmd = cmds;
	pid = -1;
	while (cmd)
	{
		if (cmd->next)
		{
			if (pipe(pipefd) == -1)
				return (-1);
		}
		pid = fork_and_exec(cmd, shell, in_fd, pipefd);
		if (pid < 0)
			return (-1);
		if (cmd->next)
			in_fd = pipefd[0];
		cmd = cmd->next;
	}
	return (pid);
}
