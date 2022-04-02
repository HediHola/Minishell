/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauremasson <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:03:48 by lauremass         #+#    #+#             */
/*   Updated: 2022/02/25 00:52:15 by lmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	env_len(t_env *env)
{
	t_env	*count;
	int		i;

	count = env;
	i = 0;
	while (count)
	{
		i++;
		count = count->next;
	}
	return (i);
}

char	*ms_strcat(char *dst, char *src, int type)
{
	char	*final;
	size_t	len;
	size_t	y;
	size_t	i;

	len = ft_strlen(dst) + ft_strlen(src);
	i = 0;
	y = 0;
	final = malloc(sizeof(char) * len + 1);
	while (dst && dst[i])
	{
		final[i] = dst[i];
		i++;
	}
	while (src && src[y])
	{
		final[i + y] = src[y];
		y++;
	}
	final[i + y] = '\0';
	if (dst && type == 1)
		free(dst);
	return (final);
}

char	*ms_strcat_env(char *key, char *content)
{
	char	*line;
	char	*final;

	line = NULL;
	line = ms_strcat(key, "=", 0);
	final = ms_strcat(line, content, 1);
	return (final);
}

void	free_env_element(t_env *env)
{
	if (env->key)
		free(env->key);
	if (env->content)
		free(env->content);
	if (env)
		free(env);
}

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env != NULL)
	{
		if (env->next == NULL)
		{
			temp = env;
			free_env_element(temp);
			return ;
		}
		temp = env;
		env = env->next;
		free_env_element(temp);
	}
	if (env)
		free(env);
}
