/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claherna <claherna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 00:00:00 by claherna          #+#    #+#             */
/*   Updated: 2026/03/01 21:27:31 by claherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*fill_cmd(t_token *tok, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (tok && tok->type != TOKEN_PIPE)
	{
		if (tok->type == TOKEN_WORD)
		{
			cmd->args[i] = ft_strdup(tok->value);
			i++;
		}
		else
		{
			add_redir(cmd, tok->type, tok->next->value);
			tok = tok->next;
		}
		tok = tok->next;
	}
	cmd->args[i] = NULL;
	return (tok);
}

static void	cmd_add_back(t_cmd **cmds, t_cmd *new_node)
{
	t_cmd	*tmp;

	if (!*cmds)
	{
		*cmds = new_node;
		return ;
	}
	tmp = *cmds;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*cmd;
	t_token	*tok;
	int		arg_count;

	cmds = NULL;
	tok = tokens;
	while (tok)
	{
		arg_count = count_args(tok);
		cmd = new_cmd(arg_count);
		if (!cmd)
			return (cmds);
		tok = fill_cmd(tok, cmd);
		cmd_add_back(&cmds, cmd);
		if (tok && tok->type == TOKEN_PIPE)
			tok = tok->next;
	}
	return (cmds);
}
