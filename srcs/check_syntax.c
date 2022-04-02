/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <htizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 02:55:31 by htizi             #+#    #+#             */
/*   Updated: 2022/02/25 19:56:56 by lmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ends(t_list *tmp)
{
	if (tmp && (tmp->type == PIPE || tmp->type == PIPE + SPACE_FOUND))
		return (SYNTAX_ERR);
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp && type_is_op(tmp->type))
		return (SYNTAX_ERR);
	return (0);
}

int	check_syntax(t_list **list)
{
	t_list	*tmp;
	int		op_1;
	int		op_2;

	tmp = *list;
	if (check_strings_to_merge(list))
		return (MALLOC_ERR);
	if (check_ends(tmp))
		return (SYNTAX_ERR);
	while (tmp && tmp->next)
	{
		if (type_is_op(tmp->type) && type_is_op(tmp->next->type))
		{
			op_1 = type_is_op(tmp->type);
			op_2 = type_is_op(tmp->next->type);
			if ((op_1 == PIPE && op_2 == PIPE)
				|| (op_1 != PIPE && op_2 != PIPE)
				|| (op_1 != PIPE && op_2 == PIPE))
				return (SYNTAX_ERR);
		}
		tmp = tmp->next;
	}
	return (0);
}
