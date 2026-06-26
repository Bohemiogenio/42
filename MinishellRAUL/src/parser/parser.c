/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claherna <claherna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 00:00:00 by claherna          #+#    #+#             */
/*   Updated: 2026/03/01 21:27:31 by claherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_token *tok)
{
	int	count;

	count = 0;
	while (tok && tok->type != TOKEN_PIPE)
	{
		if (tok->type == TOKEN_WORD)
			count++;
		else
		{
			tok = tok->next;
			if (tok)
				tok = tok->next;
			continue ;
		}
		tok = tok->next;
	}
	return (count);
}

void	add_redir(t_cmd *cmd, t_token_type type, char *file)
{
	t_redir	*redir;
	t_redir	*tmp;
	char	*dup_file;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return ;
	dup_file = ft_strdup(file);
	if (!dup_file)
	{
		free(redir);
		return ;
	}
	redir->type = type;
	redir->file = dup_file;
	redir->next = NULL;
	if (!cmd->redirs)
	{
		cmd->redirs = redir;
		return ;
	}
	tmp = cmd->redirs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = redir;
}

t_cmd	*new_cmd(int arg_count)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	cmd->args[0] = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}
