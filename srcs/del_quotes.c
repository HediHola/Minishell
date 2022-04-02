/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <htizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 04:19:21 by htizi             #+#    #+#             */
/*   Updated: 2022/01/11 17:01:51 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	del_quotes(t_list **list)
{
	t_list	*tmp;
	char	*str;
	int		brackets_unclosed;

	tmp = *list;
	brackets_unclosed = 0;
	while (tmp)
	{
		if (tmp->type != DISPLAY_ONLY)
		{
			if (tmp->value[0] == '\'' || tmp->value[0] == '$'
				|| tmp->value[0] == '\"')
			{
				str = del_quotes_or_brackets(tmp->value, &brackets_unclosed);
				if (brackets_unclosed)
					return (BRACKETS_UNCLOSED);
				if (!str)
					return (MALLOC_ERR);
				free (tmp->value);
				tmp->value = str;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
