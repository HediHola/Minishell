/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <htizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 02:16:09 by htizi             #+#    #+#             */
/*   Updated: 2022/02/26 12:11:03 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	set_nb_pipes(t_node **nodes)
{
	t_node	*tmp_nodes;
	int		counter;

	counter = 0;
	tmp_nodes = *nodes;
	while (tmp_nodes)
	{
		if (tmp_nodes->type == PIPE)
			counter++;
		tmp_nodes = tmp_nodes->right;
	}
	tmp_nodes = *nodes;
	while (tmp_nodes)
	{
		if (tmp_nodes->type == ARGS)
			tmp_nodes->args->nb_pipes = counter;
		tmp_nodes = tmp_nodes->right;
	}
	return (0);
}

int	pipe_fds(t_node **nodes)
{
	t_node	*tmp;

	tmp = *nodes;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			tmp->fd = malloc(sizeof(int) * 2);
			if (!tmp->fd)
				return (MALLOC_ERR);
		}
		else
			tmp->fd = NULL;
		tmp = tmp->right;
	}
	return (0);
}

int	init_args(t_node **nodes, t_list **list)
{
	set_nb_pipes(nodes);
	set_redir(nodes, list);
	set_fd_lists(nodes, list);
	if (pipe_fds(nodes))
		return (-1);
	if (set_args_tab(nodes, list))
		return (MALLOC_ERR);
	find_builtin(nodes);
	return (0);
}

int	parser(t_list **list, t_node **nodes)
{
	if (init_nodes(list, nodes))
		return (MALLOC_ERR);
	if (init_args(nodes, list))
		return (MALLOC_ERROR);
	return (0);
}
