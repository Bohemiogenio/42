/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claherna <claherna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 00:00:00 by claherna          #+#    #+#             */
/*   Updated: 2026/03/06 20:03:26 by claherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_char(char *str, char c)
{
	char	buf[2];
	char	*result;

	buf[0] = c;
	buf[1] = '\0';
	if (!str)
		return (ft_strdup(buf));
	result = ft_strjoin(str, buf);
	free(str);
	if (!result)
		return (NULL);
	return (result);
}

static char	*expand_exit_status(char *result, t_shell *shell)
{
	char	*status;
	char	*tmp;

	status = ft_itoa(shell->exit_status);
	if (!result)
		return (status);
	tmp = ft_strjoin(result, status);
	free(result);
	free(status);
	return (tmp);
}

char	*expand_tilde(char *str, t_shell *shell)
{
	char	*home;
	char	*result;

	if (str[0] != '~' || (str[1] && str[1] != '/'))
		return (ft_strdup(str));
	home = env_get(shell->env, "HOME");
	if (!home)
		return (ft_strdup(str));
	result = ft_strjoin(home, str + 1);
	return (result);
}

char	*expand_var_name(char *str, int *i, char *result, t_shell *shell)
{
	int		start;
	char	*key;
	char	*val;
	char	*tmp;

	if (str[*i] == '?')
	{
		(*i)++;
		return (expand_exit_status(result, shell));
	}
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	if (*i == start)
		return (append_char(result, '$'));
	key = ft_substr(str, start, *i - start);
	val = env_get(shell->env, key);
	free(key);
	if (!val)
		return (result);
	if (!result)
		return (ft_strdup(val));
	tmp = ft_strjoin(result, val);
	free(result);
	return (tmp);
}
