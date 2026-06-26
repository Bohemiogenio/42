/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claherna <claherna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 00:00:00 by claherna          #+#    #+#             */
/*   Updated: 2026/03/01 21:27:32 by claherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*try_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	if (access(full, X_OK) == 0)
		return (full);
	free(full);
	return (NULL);
}

static char	*search_in_path(char *cmd, char *path_str)
{
	char	**dirs;
	char	*result;
	int		i;

	dirs = ft_split(path_str, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	result = NULL;
	while (dirs[i])
	{
		result = try_path(dirs[i], cmd);
		if (result)
			break ;
		i++;
	}
	free_array(dirs);
	return (result);
}

char	*find_command_path(char *cmd, t_env *env)
{
	char	*path_str;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_str = env_get(env, "PATH");
	if (!path_str)
		return (NULL);
	return (search_in_path(cmd, path_str));
}
