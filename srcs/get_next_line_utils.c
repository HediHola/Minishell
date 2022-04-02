/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 12:05:10 by lmasson           #+#    #+#             */
/*   Updated: 2022/02/24 19:22:43 by lauremass        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncat(char *dst, char *src, int len)
{
	int	i;
	int	dst_len;

	i = 0;
	dst_len = ft_strlen(dst);
	while (src[i] && src && i < len)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst);
}

char	*gn_strcpy(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i] && src)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
