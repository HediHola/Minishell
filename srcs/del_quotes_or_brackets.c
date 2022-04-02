/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quotes_or_brackets.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <htizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 05:30:40 by htizi             #+#    #+#             */
/*   Updated: 2022/02/25 15:47:44 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cpy_str_without_quotes(char *str)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	dest = (char *)malloc(sizeof(char) * i - 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == str[0])
			i++;
		if (str[i] && str[i] != str[0])
		{
			dest[j] = str[i];
			j++;
			i++;
		}
	}
	dest[j] = '\0';
	return (dest);
}

char	*del_curly_brackets(char **str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((*str)[j] != '}')
		j++;
	new_str = malloc(sizeof(char) * j);
	if (!new_str)
		return (NULL);
	while (**str)
	{
		if (**str != '{' && **str != '}')
			new_str[i++] = **str;
		if (**str == '}')
		{
			new_str[i] = '\0';
			(*str)++;
			return (new_str);
		}
		(*str)++;
	}
	return (NULL);
}

int	print_brackets_err_msg(int open, int closed)
{
	if (open == 1 && closed == 1)
		return (0);
	if (open > 0 && closed == 0)
	{
		fd_printnl("minishell: Unmatched curly brackets", STDERR_FILENO);
		return (1);
	}
	if (open > 0 && closed > 0)
	{
		fd_printnl("minishell: Bad substitution", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	check_curly_brackets(char *str)
{
	int	open;
	int	closed;
	int	i;

	open = 0;
	closed = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '{')
			open++;
		if (str[i] == '}')
		{
			closed++;
			break ;
		}
		i++;
	}
	return (print_brackets_err_msg(open, closed));
}

char	*del_quotes_or_brackets(char *str, int *brackets_unclosed)
{
	char	*dest;

	if (str[0] == '$' && str[1] == '{')
	{
		if (check_curly_brackets(str))
		{
			(*brackets_unclosed)++;
			return (NULL);
		}
		return (del_curly_brackets(&str));
	}
	if (!(str[0] == '\'' || str[0] == '\"'))
		return (ft_strdup(str));
	dest = cpy_str_without_quotes(str);
	if (!dest)
		return (NULL);
	return (dest);
}
