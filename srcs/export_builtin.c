/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauremasson <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:12:54 by lauremass         #+#    #+#             */
/*   Updated: 2022/02/25 02:14:41 by lmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*manage_content(char *args, t_export type, char *key)
{
	char	*content;
	int		i;
	int		y;

	i = ft_strlen(key) + 1;
	y = ft_strlen(args);
	content = NULL;
	if (type == F_CONCAT)
		i++;
	if (i == y)
		return (ft_strdup(""));
	content = malloc(sizeof(char *) * (y - i));
	if (!content)
		return (NULL);
	y = 0;
	while (args[i])
	{
		content[y] = args[i++];
		y++;
	}
	content[y] = '\0';
	return (content);
}

t_export	define_type_export(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i++] == '=')
		{
			if (i > 2 && args[i - 2] == '+')
				return (F_CONCAT);
			return (F_TRUNC);
		}
	}
	return (E_TRUNC);
}

char	*split_key(char *args, t_export type)
{
	char	**split;
	int		i;
	char	*key;

	split = NULL;
	key = NULL;
	i = 0;
	split = ft_split(args, '=');
	if (!split)
		return (NULL);
	key = split[0];
	i = ft_strlen(key);
	if (type == F_CONCAT)
		key = ft_strndup(key, i - 1);
	else
		key = ft_strndup(key, i);
	if (split)
		free_double_tab(split);
	return (key);
}

char	*manage_key(char *args, t_export type)
{
	char	*key;

	key = NULL;
	if (args[0] == '=')
		key = ft_strdup("=");
	else if (type == F_CONCAT || type == F_TRUNC)
		key = split_key(args, type);
	else
		key = ft_strdup(args);
	if (!key)
		return (NULL);
	return (key);
}

int	update_env(char	*key, char *content, t_env **env, t_export type)
{
	t_env	*tmp;
	char	*to_free;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			to_free = tmp->content;
			if (type == F_CONCAT)
				content = ms_strcat(to_free, content, 1);
			tmp->content = ft_strdup(content);
			if (type == F_CONCAT)
				free(content);
			else
			{
				if (to_free)
					free(to_free);
			}
			return (g_data.last_return = COMMAND_WORK);
		}
		tmp = tmp->next;
	}
	return (g_data.last_return = WRONG_ARG);
}
