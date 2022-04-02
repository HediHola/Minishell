/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauremasson <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:55:49 by lauremass         #+#    #+#             */
/*   Updated: 2022/02/24 19:48:58 by lauremass        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ms_getenv(char *key, t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
			return (temp->content);
		temp = temp->next;
	}
	return (NULL);
}

t_env	*add_env_element_bottom(t_env *env, char *key, char *content)
{
	t_env	*e;
	t_env	*temp;

	e = env;
	temp = env_element_create(key, content);
	if (!temp)
		return (NULL);
	if (env == NULL)
		return (temp);
	else
	{
		while (e->next != NULL)
			e = e->next;
		e->next = temp;
	}
	return (env);
}

t_env	*add_env_element_top(t_env *env, char *key, char *content)
{
	t_env	*temp;

	temp = env_element_create(key, content);
	if (!temp)
		return (NULL);
	if (env == NULL)
		return (temp);
	temp->next = env;
	env = temp;
	return (env);
}

t_env	*env_element_create(char *key, char *content)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	env->content = ft_strdup(content);
	env->next = NULL;
	return (env);
}
