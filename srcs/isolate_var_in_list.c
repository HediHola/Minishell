/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isolate_var_in_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <htizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 04:24:11 by htizi             #+#    #+#             */
/*   Updated: 2022/02/25 15:44:10 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restart_loop(t_list **list, t_list **tmp, int *pos)
{
	t_list	*elem_to_free;

	elem_to_free = *tmp;
	*tmp = *list;
	*pos = 0;
	ft_free_elem(&elem_to_free);
}

int	check_d_quote(char *line)
{
	if (closed_quotes(line))
		return (QUOTES_UNCLOSED);
	if (line[0] != '\"')
		return (1);
	return (0);
}

int	look_for_var(t_list **list, char *line, int pos)
{
	int	i;
	int	brackets_unclosed;

	i = 0;
	brackets_unclosed = 0;
	if (check_d_quote(line))
		return (0);
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (patch_list(list, pos, &brackets_unclosed))
			{
				if (brackets_unclosed)
					return (BRACKETS_UNCLOSED);
				return (MALLOC_ERR);
			}
			return (VAR_FOUND);
		}
		i++;
	}
	return (0);
}

int	isolate_var_in_list(t_list **list)
{
	t_list	*tmp;
	int		pos;
	int		ret;

	tmp = *list;
	pos = 0;
	while (tmp)
	{
		ret = look_for_var(list, tmp->value, pos);
		if (ret == BRACKETS_UNCLOSED)
			return (BRACKETS_UNCLOSED);
		if (ret == MALLOC_ERR)
			return (MALLOC_ERR);
		if (ret == VAR_FOUND)
			restart_loop(list, &tmp, &pos);
		tmp = tmp->next;
		pos++;
	}
	return (0);
}
