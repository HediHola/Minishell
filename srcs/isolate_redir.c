/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isolate_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <htizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 03:05:18 by htizi             #+#    #+#             */
/*   Updated: 2022/02/06 13:52:07 by lauremass        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	start_files_list(t_list **list, t_list **files_list)
{
	t_list	*tmp_list_post_file;

	tmp_list_post_file = (*list)->next->next;
	*files_list = *list;
	if ((*list)->prev)
		(*list)->prev->next = (*list)->next->next;
	if ((*list)->next->next)
		(*list)->next->next->prev = (*list)->prev;
	(*list)->next->next = NULL;
	(*list)->prev = NULL;
	*list = tmp_list_post_file;
	return (0);
}

int	add_to_files_list(t_list **list, t_list **files_list)
{
	t_list	*tmp_list_post_file;

	tmp_list_post_file = (*list)->next->next;
	while ((*files_list)->next)
		*files_list = (*files_list)->next;
	(*files_list)->next = *list;
	(*list)->prev->next = (*list)->next->next;
	if ((*list)->next->next)
		(*list)->next->next->prev = (*list)->prev;
	(*list)->prev = (*files_list);
	(*list)->next->next = NULL;
	while ((*files_list)->prev)
		(*files_list) = (*files_list)->prev;
	*list = tmp_list_post_file;
	return (0);
}

int	push_to_infiles_list(t_list **list, t_node **nodes)
{
	if ((*nodes)->args->infiles)
		add_to_files_list(list, &(*nodes)->args->infiles);
	else
		start_files_list(list, &(*nodes)->args->infiles);
	return (0);
}

int	push_to_outfiles_list(t_list **list, t_node **nodes)
{
	if ((*nodes)->args->outfiles)
		add_to_files_list(list, &(*nodes)->args->outfiles);
	else
		start_files_list(list, &(*nodes)->args->outfiles);
	return (0);
}

int	isolate_redir(t_list **list, t_node **nodes)
{
	if ((*list)->type == SL_REDIRECTION || (*list)->type == DL_REDIRECTION)
		push_to_infiles_list(list, nodes);
	else if ((*list)->type == SR_REDIRECTION || (*list)->type == DR_REDIRECTION)
		push_to_outfiles_list(list, nodes);
	return (0);
}
