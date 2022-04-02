/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:13:50 by lmasson           #+#    #+#             */
/*   Updated: 2022/02/20 13:17:30 by lauremass        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (i);
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_substr(char *s, int start, size_t len)
{
	char			*s_bis;
	size_t			i;
	size_t			len_to_copy;

	i = 0;
	if (!s)
		return (NULL);
	len_to_copy = ft_strlen(&s[start]);
	if (len_to_copy < len)
		len = len_to_copy;
	if (ft_strlen(s) <= start || len <= 0)
		return (ft_strdup(""));
	s_bis = malloc(sizeof(char) * (len + 1));
	if (!s_bis)
		return (NULL);
	while (i < len && s[start + i])
	{
		s_bis[i] = s[start + i];
		i++;
	}
	s_bis[i] = '\0';
	return (s_bis);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strdup(char *s1)
{
	int		len;
	int		i;
	char	*final;

	len = ft_strlen(s1) + 1;
	i = 0;
	if (s1 == NULL)
		return (ft_strdup(""));
	final = malloc((sizeof(char) * len));
	if (!final)
		return (NULL);
	while (s1[i])
	{
		final[i] = s1[i];
		i++;
	}
	final[i] = '\0';
	return (final);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		total_len;
	int		i;
	int		n;
	char	*final;

	i = 0;
	n = 0;
	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	final = malloc(sizeof(char) * total_len);
	if (!final)
		return (NULL);
	while (s1[n])
		final[i++] = (char)s1[n++];
	n = 0;
	while (s2[n])
	{
		final[i++] = (char)s2[n];
		n++;
	}
	final[i] = '\0';
	return (final);
}
