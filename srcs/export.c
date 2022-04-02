/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 00:54:13 by lmasson           #+#    #+#             */
/*   Updated: 2022/02/25 18:44:34 by lmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	export_full(char *key, char *content, t_env *env, t_export type)
{
	if (is_env_exist(key, env) == 1)
		update_env(key, content, &env, type);
	else
		env = add_env_element_bottom(env, key, content);
}

void	execute_export(char *key, char *content, t_export type)
{
	if (type == F_CONCAT || type == F_TRUNC)
	{
		export_full(key, content, g_data.env, type);
		export_full(key, content, g_data.export_env, type);
	}
	else
		export_full(key, content, g_data.export_env, type);
}

void	free_export(char *key, char *content)
{
	if (key)
		free(key);
	if (content)
		free(content);
	update_char_env(&g_data);
}

int	export(char *args)
{
	t_export		type;
	char			*key;
	char			*content;

	key = NULL;
	content = NULL;
	type = NONE;
	type = define_type_export(args);
	key = manage_key(args, type);
	if (!key)
		return (0);
	if (is_valid_key(key, EXPORT) == 0)
	{
		free(key);
		return (g_data.last_return = WRONG_ARG);
	}
	if (type == F_CONCAT || type == F_TRUNC)
		content = manage_content(args, type, key);
	else
		content = ft_strdup("");
	execute_export(key, content, type);
	free_export(key, content);
	return (g_data.last_return);
}

int	exec_export(t_args *args)
{
	int		i;

	i = 1;
	if (args->args_tab[1] == NULL)
	{
		exec_env(g_data.export_env, args->is_builtin);
		return (g_data.last_return = COMMAND_WORK);
	}
	else
	{
		while (args->args_tab[i])
		{
			export(args->args_tab[i]);
			i++;
		}
	}
	return (g_data.last_return);
}
