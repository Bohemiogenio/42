/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claherna <claherna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 00:00:00 by claherna          #+#    #+#             */
/*   Updated: 2026/03/06 20:03:48 by claherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_dquote(char *str, int *i, char *res, t_shell *shell)
{
	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$' && str[*i + 1])
		{
			(*i)++;
			res = expand_var_name(str, i, res, shell);
		}
		else
			res = append_char(res, str[(*i)++]);
	}
	if (str[*i] == '"')
		(*i)++;
	return (res);
}

static char	*handle_squote(char *str, int *i, char *result)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		result = append_char(result, str[(*i)++]);
	if (str[*i] == '\'')
		(*i)++;
	return (result);
}

char	*expand_string(char *str, t_shell *shell)
{
	char	*result;
	int		i;

	result = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			result = handle_squote(str, &i, result);
		else if (str[i] == '"')
			result = handle_dquote(str, &i, result, shell);
		else if (str[i] == '$' && str[i + 1])
		{
			i++;
			result = expand_var_name(str, &i, result, shell);
		}
		else
			result = append_char(result, str[i++]);
	}
	if (!result)
		result = ft_strdup("");
	return (result);
}

t_token	*expand_tokens(t_token *tokens, t_shell *shell)
{
	t_token	*tok;
	char	*expanded;

	tok = tokens;
	while (tok)
	{
		if (tok->type == TOKEN_WORD)
		{
			expanded = expand_tilde(tok->value, shell);
			free(tok->value);
			tok->value = expand_string(expanded, shell);
			free(expanded);
		}
		tok = tok->next;
	}
	return (tokens);
}
