/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claherna <claherna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 00:00:00 by claherna          #+#    #+#             */
/*   Updated: 2026/03/01 21:27:30 by claherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*env_new_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

static void	env_add_back(t_env **env, t_env *new_node)
{
	t_env	*tmp;

	if (!*env)
	{
		*env = new_node;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

static t_env	*parse_env_entry(char *entry)
{
	char	*eq;
	char	*key;
	t_env	*node;

	eq = ft_strchr(entry, '=');
	if (!eq)
		return (NULL);
	key = ft_substr(entry, 0, eq - entry);
	node = env_new_node(key, eq + 1);
	free(key);
	return (node);
}

t_env	*env_init(char **envp)
{
	t_env	*env;
	t_env	*node;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		node = parse_env_entry(envp[i]);
		if (node)
			env_add_back(&env, node);
		i++;
	}
	return (env);
}
