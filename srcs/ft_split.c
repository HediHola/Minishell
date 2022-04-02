/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:18:47 by lmasson           #+#    #+#             */
/*   Updated: 2022/02/06 14:07:21 by lauremass        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	is_sep(char schar, char sep)
{
	if (schar == sep)
		return (1);
	return (0);
}

size_t	count_word(char *s_bis, char c_sep)
{
	size_t	i;
	size_t	count;

	i = 1;
	count = 0;
	if (!is_sep(s_bis[0], c_sep))
		count++;
	while (s_bis[i])
	{
		if (is_sep(s_bis[i - 1], c_sep) == 1 && is_sep(s_bis[i], c_sep) == 0)
			count++;
		i++;
	}
	return (count);
}

size_t	length_word(char *s_b, char spec, size_t i)
{
	size_t	m;

	m = 0;
	while (!is_sep(s_b[i + m], spec) && s_b[i + m])
		m++;
	return (m);
}

void	*free_double_tab(char **tab)
{
	int		i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (NULL);
}

char	**ft_split(char *s, char c)
{
	size_t	x;
	size_t	n;
	char	**tab;

	x = 0;
	n = 0;
	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!tab)
		return (NULL);
	while (s[n])
	{
		if ((!is_sep(s[n], c) && n == 0)
			|| (!is_sep(s[n], c) && is_sep(s[n - 1], c)))
		{
			tab[x++] = ft_substr(s, n, length_word(s, c, n));
			if (!tab)
				return (free_double_tab(tab));
		}
		n++;
	}
	tab[x] = 0;
	return (tab);
}
