/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <htizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:13:46 by htizi             #+#    #+#             */
/*   Updated: 2022/02/06 14:04:04 by lauremass        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	set_flag(t_list *list, t_node **nodes)
{
	if (list->type == SL_REDIRECTION || list->type == DL_REDIRECTION)
		(*nodes)->args->redir_in = 1;
	if (list->type == SR_REDIRECTION || list->type == DR_REDIRECTION)
		(*nodes)->args->redir_out = 1;
	return (0);
}

int	set_redir(t_node **nodes, t_list **list)
{
	t_list	*tmp_list;
	t_node	*tmp_nodes;

	tmp_list = *list;
	tmp_nodes = *nodes;
	while (tmp_list)
	{
		if (tmp_list->type == PIPE)
		{
			tmp_list = tmp_list->next;
			tmp_nodes = tmp_nodes->right->right;
		}
		set_flag(tmp_list, &tmp_nodes);
		tmp_list = tmp_list->next;
	}
	return (0);
}
