/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 15:24:25 by htizi             #+#    #+#             */
/*   Updated: 2022/01/11 15:20:24 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	increment_i_and_len(int *i, int *len)
{
	(*i)++;
	(*len)++;
}

int	is_var(char *line, int *i, int *len)
{
	if (line[*i] && (line[*i] != '$'))
		return (0);
	if (*len)
		return (1);
	while (line[*i + 1] && (char_is_valid(line[*i + 1])
			|| is_curly_bracket(line[*i + 1])))
	{
		increment_i_and_len(i, len);
		if (is_curly_bracket(line[*i]) == 1)
		{
			while (line[*i + 1] && line[*i] != '}')
				increment_i_and_len(i, len);
		}
		if (is_curly_bracket(line[*i]) == 2)
			break ;
	}
	if (line[1] != '}')
		increment_i_and_len(i, len);
	return (1);
}

int	is_pipe(char *line, int *i, int *len)
{
	if (line[*i] && (line[*i] != '|'))
		return (0);
	if (*len)
		return (1);
	(*len)++;
	(*i)++;
	return (1);
}

int	is_redirection(char *line, int *i, int *len)
{
	if (line[*i] && (line[*i] != '<' && line[*i] != '>'))
		return (0);
	if (*len)
		return (1);
	(*len)++;
	(*i)++;
	if (line[*i] && line[*i] == line[*i - 1])
	{
		(*len)++;
		(*i)++;
	}
	return (1);
}

int	is_quote(char *line, int *i, int *len)
{
	int	j;

	j = *i;
	if (line[*i] && (line[*i] != '\'' && line[*i] != '\"'))
		return (0);
	if (*len)
		return (1);
	(*len)++;
	(*i)++;
	while (line[*i] && line[*i] != line[j])
	{
		(*len)++;
		(*i)++;
	}
	if (line[*i])
	{
		(*len)++;
		(*i)++;
	}
	return (1);
}
