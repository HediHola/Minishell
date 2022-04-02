/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 16:09:02 by htizi             #+#    #+#             */
/*   Updated: 2022/01/30 03:15:01 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	op_found(char *line, int *i, int *len)
{
	if (is_quote(line, i, len))
		return (1);
	if (is_redirection(line, i, len))
		return (1);
	if (is_pipe(line, i, len))
		return (1);
	if (is_var(line, i, len))
		return (1);
	return (0);
}

int	set_substr_len(char *line, int *i)
{
	int	len;

	len = 0;
	while (line[*i] && !ft_is_space(line[*i]))
	{
		if (op_found(line, i, &len))
			return (len);
		len++;
		(*i)++;
	}
	return (len);
}

int	set_substr_start(char *line, int *i, int *space_found)
{	
	if (line[*i] && ft_is_space(line[*i]))
	{
		*space_found = 1;
		while (line[*i] && ft_is_space(line[*i]))
			(*i)++;
	}
	return (*i);
}

void	add_flag_to_type(t_list **list, int flag)
{
	t_list	*tmp;

	tmp = ft_list_last(*list);
	if (tmp->prev)
		tmp->prev->type += flag;
}

int	create_list(t_list **list, char *line)
{
	int		len;
	int		start;
	int		i;
	int		ret;
	int		space_found;

	i = 0;
	while (line[i])
	{
		space_found = 0;
		start = set_substr_start(line, &i, &space_found);
		if (!line[i])
			return (0);
		len = set_substr_len(line, &i);
		ret = ft_list_push_back(list, ms_substr(line, start, len));
		if (ret == MALLOC_ERR)
			return (MALLOC_ERR);
		if (space_found == 1)
			add_flag_to_type(list, SPACE_FOUND);
	}
	return (0);
}
