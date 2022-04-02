/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 14:47:29 by htizi             #+#    #+#             */
/*   Updated: 2021/12/30 22:02:58 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*cpy;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	str = (char *)s;
	cpy = (char *)malloc(sizeof(char) * (len + 1));
	if (!cpy)
		return (NULL);
	while (str[start] && len > 0)
	{
		cpy[i++] = str[start++];
		len--;
	}
	cpy[i] = '\0';
	return (cpy);
}
