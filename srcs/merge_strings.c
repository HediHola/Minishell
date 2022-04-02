/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <htizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 03:13:19 by htizi             #+#    #+#             */
/*   Updated: 2022/02/06 13:54:41 by lauremass        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_string(char **dest, char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[j])
		(*dest)[i++] = s1[j++];
	j = 0;
	while (s2[j])
		(*dest)[i++] = s2[j++];
	(*dest)[i] = '\0';
}

void	rearrange_list(char *str, int pos, t_list **list)
{
	t_list	*tmp;
	t_list	*elem_to_free;

	tmp = *list;
	while (pos--)
		tmp = tmp->next;
	free (tmp->value);
	tmp->value = str;
	elem_to_free = tmp->next;
	if (tmp->next->next)
		tmp->next->next->prev = tmp;
	tmp->next = tmp->next->next;
	ft_free_elem(&elem_to_free);
}

int	merge_strings(t_list **list, int pos)
{
	t_list	*tmp;
	int		i;
	int		tmp_pos;
	char	*str;

	i = 0;
	tmp = *list;
	tmp_pos = pos;
	while (pos--)
		tmp = tmp->next;
	i = ft_strlen(tmp->value) + ft_strlen(tmp->next->value);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (MALLOC_ERR);
	fill_string(&str, tmp->value, tmp->next->value);
	tmp->type = tmp->next->type;
	rearrange_list(str, tmp_pos, list);
	return (0);
}

int	type_is_op(int type)
{
	if (type == SL_REDIRECTION || type == SL_REDIRECTION + SPACE_FOUND)
		return (1);
	if (type == DL_REDIRECTION || type == DL_REDIRECTION + SPACE_FOUND)
		return (1);
	if (type == SR_REDIRECTION || type == SR_REDIRECTION + SPACE_FOUND)
		return (1);
	if (type == DR_REDIRECTION || type == DR_REDIRECTION + SPACE_FOUND)
		return (1);
	if (type == PIPE || type == PIPE + SPACE_FOUND)
		return (PIPE);
	return (0);
}

int	check_strings_to_merge(t_list **list)
{
	t_list	*tmp;
	int		pos;

	tmp = *list;
	pos = 0;
	while (tmp && tmp->next)
	{
		if (tmp->type < SPACE_FOUND && !type_is_op(tmp->next->type)
			&& !type_is_op(tmp->type))
		{
			if (merge_strings(list, pos))
				return (MALLOC_ERR);
			tmp = *list;
			pos = 0;
		}
		else
		{
			tmp = tmp->next;
			pos++;
		}
	}
	return (0);
}
