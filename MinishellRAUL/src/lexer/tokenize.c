/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claherna <claherna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 00:00:00 by claherna          #+#    #+#             */
/*   Updated: 2026/03/01 21:27:30 by claherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_quotes(char *line, int i, char quote)
{
	i++;
	while (line[i] && line[i] != quote)
		i++;
	if (line[i] == quote)
		i++;
	return (i);
}

static int	get_word_end(char *line, int i)
{
	while (line[i] && line[i] != ' ' && line[i] != '\t'
		&& line[i] != '|' && line[i] != '<' && line[i] != '>')
	{
		if (line[i] == '\'' || line[i] == '"')
			i = skip_quotes(line, i, line[i]);
		else
			i++;
	}
	return (i);
}

static int	tokenize_operator(char *line, int i, t_token **tokens)
{
	if (line[i] == '|')
		token_add_back(tokens, token_new(TOKEN_PIPE, ft_strdup("|")));
	else if (line[i] == '<' && line[i + 1] == '<')
	{
		token_add_back(tokens, token_new(TOKEN_HEREDOC, ft_strdup("<<")));
		return (i + 2);
	}
	else if (line[i] == '>' && line[i + 1] == '>')
	{
		token_add_back(tokens, token_new(TOKEN_APPEND, ft_strdup(">>")));
		return (i + 2);
	}
	else if (line[i] == '<')
		token_add_back(tokens, token_new(TOKEN_REDIR_IN, ft_strdup("<")));
	else if (line[i] == '>')
		token_add_back(tokens, token_new(TOKEN_REDIR_OUT, ft_strdup(">")));
	return (i + 1);
}

static int	tokenize_word(char *line, int i, t_token **tokens)
{
	int		end;
	char	*word;

	end = get_word_end(line, i);
	word = ft_substr(line, i, end - i);
	token_add_back(tokens, token_new(TOKEN_WORD, word));
	return (end);
}

t_token	*tokenize(char *line)
{
	t_token	*tokens;
	int		i;

	if (!line)
		return (NULL);
	tokens = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
			i = tokenize_operator(line, i, &tokens);
		else
			i = tokenize_word(line, i, &tokens);
	}
	return (tokens);
}
