/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claherna <claherna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 00:00:00 by claherna          #+#    #+#             */
/*   Updated: 2026/03/01 21:27:31 by claherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *line)
{
	char	q;
	int		i;

	q = 0;
	i = 0;
	while (line[i])
	{
		if (!q && (line[i] == '\'' || line[i] == '"'))
			q = line[i];
		else if (q && line[i] == q)
			q = 0;
		i++;
	}
	if (q)
	{
		ft_putendl_fd("minishell: syntax error: unclosed quote",
			STDERR_FILENO);
		return (1);
	}
	return (0);
}

static int	is_redir(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_HEREDOC || type == TOKEN_APPEND);
}

static int	syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	return (1);
}

static int	check_pipe_errors(t_token *tok)
{
	if (tok->type == TOKEN_PIPE && !tok->next)
		return (syntax_error("|"));
	if (tok->type == TOKEN_PIPE && tok->next->type == TOKEN_PIPE)
		return (syntax_error("|"));
	return (0);
}

int	check_syntax(t_token *tokens)
{
	t_token	*tok;

	if (!tokens)
		return (0);
	if (tokens->type == TOKEN_PIPE)
		return (syntax_error("|"));
	tok = tokens;
	while (tok)
	{
		if (is_redir(tok->type) && (!tok->next
				|| tok->next->type != TOKEN_WORD))
			return (syntax_error(tok->value));
		if (tok->type == TOKEN_PIPE && check_pipe_errors(tok))
			return (1);
		tok = tok->next;
	}
	return (0);
}
