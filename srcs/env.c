/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauremasson <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:42:37 by lauremass         #+#    #+#             */
/*   Updated: 2022/02/25 02:08:31 by lmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_strlen_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

t_env	*set_basic_env(t_env *env, int type)
{
	char	*actual_dir;

	(void)type;
	actual_dir = getcwd(NULL, 0);
	if (!actual_dir)
		return (NULL);
	env = add_env_element_bottom(env, "PWD", actual_dir);
	env = add_env_element_bottom(env, "OLDPWD", actual_dir);
	env = add_env_element_bottom(env, "PATH",
			"/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	free(actual_dir);
	return (env);
}

char	*create_content(char **split)
{
	char	*content;
	int		i;
	int		len;

	i = 1;
	content = NULL;
	len = ft_strlen_tab(split) - 1;
	while (split[i])
	{
		content = ms_strcat(content, split[i], 1);
		if (i < len)
			content = ms_strcat(content, "=", 1);
		i++;
	}
	return (content);
}

void	free_set_env(char **temp, char *content)
{
	free_double_tab(temp);
	if (content)
		free(content);
}

void	update_char_env(t_data *g_data)
{
	free_double_tab(g_data->envi);
	g_data->envi = get_env_exec(g_data->env);
}
