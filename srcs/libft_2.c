/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauremasson <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:28:38 by lauremass         #+#    #+#             */
/*   Updated: 2022/02/21 21:27:44 by lauremass        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_strcpy(char *dst, char *src)
{
	int	i;

	i = 0;
	if (!dst || !src)
		return (0);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (0);
}

int	ft_strncpy(char *dst, char *src, int len)
{
	int	i;

	i = 0;
	if (!dst || !src)
		return (0);
	while (src[i] && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (0);
}

/*char	*ft_strndup(char *s1, int len)
{
	int		i;
	char	*final;

	i = 0;
	if (s1 == NULL)
		return (ft_strdup(""));
	final = malloc((sizeof(char) * len));
	if (!final)
		return (NULL);
	while (s1[i] && i < len)
	{
		final[i] = s1[i];
		i++;
	}
	final[i] = '\0';
	return (final);
}*/
