/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 00:30:22 by lmasson           #+#    #+#             */
/*   Updated: 2022/02/25 02:28:04 by lmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	delete_env(t_env **env, char *key)
{
	t_env	*temp;
	t_env	*prev;

	temp = *env;
	prev = NULL;
	if (temp != NULL && ft_strcmp(temp->key, key) == 0)
	{
		*env = temp->next;
		free_env_element(temp);
	}
	else
	{
		while (temp != NULL && ft_strcmp(temp->key, key))
		{
			prev = temp;
			temp = temp->next;
		}
		if (temp == NULL)
			return (g_data.last_return = 0);
		prev->next = temp->next;
		free_env_element(temp);
	}
	return (g_data.last_return = 0);
}

int	exec_unset(t_args *args)
{
	int	i;

	i = 1;
	if (args->args_tab[i] == NULL)
		return (g_data.last_return = 0);
	if (!is_valid_key(args->args_tab[i], UNSET))
		return (g_data.last_return = WRONG_ARG);
	while (args->args_tab[i])
	{
		if (is_env_exist(args->args_tab[i], g_data.env))
			delete_env(&g_data.env, args->args_tab[i]);
		if (is_env_exist(args->args_tab[i], g_data.export_env))
			delete_env(&g_data.export_env, args->args_tab[i]);
		i++;
	}
	update_char_env(&g_data);
	return (g_data.last_return = COMMAND_WORK);
}
