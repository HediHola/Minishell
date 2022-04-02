/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <htizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 23:58:28 by htizi             #+#    #+#             */
/*   Updated: 2022/01/11 15:21:06 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(char **str)
{
	int		i;
	char	*var;

	i = 0;
	while ((*str)[i + 1] && char_is_valid((*str)[i + 1]))
		i++;
	var = malloc(sizeof(char) * (i + 2));
	if (!var)
		return (NULL);
	i = 0;
	var[i++] = **str;
	(*str)++;
	while (**str && char_is_valid(**str))
	{
		var[i++] = **str;
		(*str)++;
	}
	var[i++] = '\0';
	return (var);
}

int	is_curly_bracket(char c)
{
	if (c == '{')
		return (1);
	if (c == '}')
		return (2);
	return (0);
}

char	*copy_var(char **str, int *brackets_unclosed)
{
	int		ret;
	char	*var;

	*brackets_unclosed = 0;
	if ((*str)[1] == '{')
	{
		ret = check_curly_brackets(*str);
		if (ret)
		{
			*brackets_unclosed = 1;
			return (NULL);
		}
		var = del_curly_brackets(str);
		if (!var)
			return (NULL);
		return (var);
	}
	return (get_var(str));
}

int	fill_tab(char **tab, char *str, int *brackets_unclosed)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*str)
	{
		if (*str != '$')
		{
			tab[i] = ms_strcpyt(str, '$');
			if (!tab[i])
				return (1);
			i++;
			while (*str && *str != '$')
				str++;
		}
		if (*str == '$')
		{
			tab[i++] = copy_var(&str, brackets_unclosed);
			if (!tab[i - 1])
				return (MALLOC_ERR);
		}
	}
	tab[i] = NULL;
	return (0);
}

int	count_lines(char *line)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (line[i])
	{
		if (line[i] != '$')
		{
			counter++;
			while (line[i] && line[i] != '$')
				i++;
		}
		if (line[i] == '$')
		{
			counter++;
			while (line[i + 1] && (char_is_valid(line[i + 1])
					|| is_curly_bracket(line[i + 1])))
				i++;
		}
		if (line[i] == '$')
			i++;
	}
	return (counter);
}
