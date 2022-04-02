/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <htizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 03:08:24 by htizi             #+#    #+#             */
/*   Updated: 2022/02/06 14:02:07 by lauremass        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_node(t_list **tmp_list, t_node **tmp_nodes)
{
	while (*tmp_list && (*tmp_list)->type != PIPE)
	{
		while (*tmp_list && (*tmp_list)->type == WORD)
			*tmp_list = (*tmp_list)->next;
		if (*tmp_list && type_is_op((*tmp_list)->type) != PIPE)
			isolate_redir(tmp_list, tmp_nodes);
	}
	if (*tmp_list && (*tmp_list)->type == PIPE)
	{
		*tmp_list = (*tmp_list)->next;
		*tmp_nodes = (*tmp_nodes)->right->right;
	}
	return (0);
}

int	skip_node(t_list **tmp_list, t_node **tmp_nodes)
{
	while (*tmp_list && (*tmp_list)->type != PIPE)
		*tmp_list = (*tmp_list)->next;
	if (*tmp_list)
	{
		*tmp_list = (*tmp_list)->next;
		*tmp_nodes = (*tmp_nodes)->right->right;
	}
	return (0);
}

int	set_fd_lists(t_node **nodes, t_list **list)
{
	t_list	*tmp_list;
	t_list	*elem_to_free;
	t_node	*tmp_nodes;

	ft_list_push_front(list, ft_strdup("setting_elem"));
	tmp_list = *list;
	tmp_nodes = *nodes;
	while (tmp_list)
	{
		if (!tmp_nodes->args->redir_in && !tmp_nodes->args->redir_out)
			skip_node(&tmp_list, &tmp_nodes);
		if (tmp_list && (tmp_nodes->args->redir_in
				|| tmp_nodes->args->redir_out))
			handle_node(&tmp_list, &tmp_nodes);
	}
	elem_to_free = *list;
	*list = (*list)->next;
	if (*list)
		(*list)->prev = NULL;
	ft_free_elem(&elem_to_free);
	return (0);
}
