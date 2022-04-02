/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauremasson <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:01:14 by lauremass         #+#    #+#             */
/*   Updated: 2022/02/25 02:04:51 by lmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_data(char **envp)
{
	g_data.env = set_env(envp, 1);
	if (!g_data.env)
		return ;
	g_data.export_env = set_env(envp, 2);
	if (!g_data.export_env)
		return ;
	g_data.envi = get_env_exec(g_data.env);
	if (!g_data.envi)
		return ;
	g_data.last_return = 0;
	g_data.exit_status = 0;
	g_data.pid = 0;
}

t_env	*set_env(char **envp, int type)
{
	int		i;
	char	**temp;
	t_env	*env;
	char	*content;

	i = 0;
	env = NULL;
	temp = NULL;
	if (!envp || (envp != NULL && !envp[0]))
		return (env = set_basic_env(env, type));
	while (envp[i])
	{
		temp = ft_split(envp[i], '=');
		content = create_content(temp);
		if (ft_strcmp(temp[0], "_"))
			env = add_env_element_bottom(env, temp[0], content);
		free_set_env(temp, content);
		i++;
	}
	if (type == 1)
		env = add_env_element_bottom(env, "_", "/usr/bin/env");
	return (env);
}

char	**get_env_exec(t_env *env)
{
	int		len;
	t_env	*copy;
	char	**env_exec;
	int		i;

	len = env_len(env);
	i = 0;
	copy = env;
	env_exec = malloc(sizeof(char *) * (len + 1));
	if (!env_exec)
		return (NULL);
	while (copy)
	{
		env_exec[i] = ms_strcat_env(copy->key, copy->content);
		copy = copy->next;
		i++;
	}
	env_exec[i] = NULL;
	return (env_exec);
}

int	is_env_exist(char *key, t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(key, temp->key) == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}
