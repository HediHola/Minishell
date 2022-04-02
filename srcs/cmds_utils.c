/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:57:58 by lmasson           #+#    #+#             */
/*   Updated: 2022/02/06 14:05:58 by lauremass        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**get_path(void)
{
	char	**path;
	char	*env;

	env = getenv("PATH");
	path = ft_split(env, ':');
	if (!path)
		return (NULL);
	free(env);
	return (path);
}

int	is_cmd(char *cmd)
{
	char	**env;
	char	*path;
	int		i;

	env = get_path();
	i = 0;
	if (cmd && access(cmd, X_OK) == 0)
		return (1);
	while (env[i])
	{
		path = ft_strjoin(env[i], "/");
		path = ft_strjoin(path, cmd);
		if (path && access(path, X_OK) == 0)
		{
			free(path);
			return (1);
		}
		free(path);
		i++;
	}
	free(env);
	return (0);
}
