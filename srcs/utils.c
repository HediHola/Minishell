/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <htizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 23:52:43 by htizi             #+#    #+#             */
/*   Updated: 2022/02/25 15:41:31 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	reset_types(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->type >= 10)
			tmp->type -= 10;
		if (tmp->type == 6 || tmp->type == 7)
			tmp->type = 0;
		tmp = tmp->next;
	}
	return (0);
}

int	lst_delone(t_list **tmp, t_list **list)
{
	t_list	*tmp_next;

	tmp_next = (*tmp)->next;
	if ((*tmp)->prev)
	{
		if ((*tmp)->next)
			(*tmp)->prev->next = (*tmp)->next;
		else
			(*tmp)->prev->next = NULL;
	}
	else
		(*list) = (*list)->next;
	if ((*tmp)->next)
	{
		if ((*tmp)->prev)
			(*tmp)->next->prev = (*tmp)->prev;
		else
			(*tmp)->next->prev = NULL;
	}
	if ((*tmp)->value)
		free((*tmp)->value);
	free(*tmp);
	*tmp = tmp_next;
	return (0);
}

int	ft_is_space(char c)
{
	if (c == '\t')
		return (1);
	if (c == '\n')
		return (1);
	if (c == '\v')
		return (1);
	if (c == '\f')
		return (1);
	if (c == '\r')
		return (1);
	if (c == ' ')
		return (1);
	return (0);
}

char	*ms_strcpyt(char *str, char c)
{
	char	*dest;
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	dest = (char *)malloc(sizeof(char) * i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
