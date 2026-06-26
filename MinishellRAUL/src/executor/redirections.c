/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claherna <claherna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 00:00:00 by claherna          #+#    #+#             */
/*   Updated: 2026/03/01 21:30:30 by claherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redir_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		print_error(file, NULL, strerror(errno));
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	open_redir_out(char *file, int append)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(file, flags, 0644);
	if (fd == -1)
	{
		print_error(file, NULL, strerror(errno));
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	apply_one_redir(t_redir *redir)
{
	if (redir->type == TOKEN_REDIR_IN)
		return (open_redir_in(redir->file));
	if (redir->type == TOKEN_REDIR_OUT)
		return (open_redir_out(redir->file, 0));
	if (redir->type == TOKEN_APPEND)
		return (open_redir_out(redir->file, 1));
	if (redir->type == TOKEN_HEREDOC)
		return (handle_heredoc(redir->file));
	return (0);
}

int	apply_redirections(t_cmd *cmd, t_shell *shell)
{
	t_redir	*redir;

	(void)shell;
	redir = cmd->redirs;
	while (redir)
	{
		if (apply_one_redir(redir) == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}
