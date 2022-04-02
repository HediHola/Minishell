/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <htizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:17:04 by htizi             #+#    #+#             */
/*   Updated: 2022/02/06 13:51:12 by lauremass        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	init_counter(t_list **list)
{
	int		counter;
	t_list	*tmp;

	tmp = *list;
	counter = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			counter++;
		tmp = tmp->next;
	}
	counter = counter * 2 + 1;
	return (counter);
}

int	init_nodes(t_list **list, t_node **nodes)
{
	t_list	*tmp;
	int		counter;

	tmp = *list;
	counter = init_counter(list);
	while (counter)
	{
		if (counter % 2 == 0)
		{
			if (ft_node_push_back(nodes, PIPE))
				return (MALLOC_ERR);
		}
		else
		{
			if (ft_node_push_back(nodes, ARGS))
				return (MALLOC_ERR);
		}
		counter--;
	}
	return (0);
}
