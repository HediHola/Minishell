/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <htizi@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:50:07 by user42            #+#    #+#             */
/*   Updated: 2022/02/19 00:22:21 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_nodes(t_node **nodes)
{
	t_node	*tmp;

	tmp = *nodes;
	while (*nodes != NULL)
	{
		tmp = (*nodes)->right;
		if ((*nodes)->type != PIPE)
		{
			if ((*nodes)->args->infiles)
				ft_list_clear(&(*nodes)->args->infiles);
			if ((*nodes)->args->outfiles)
				ft_list_clear(&(*nodes)->args->outfiles);
			if ((*nodes)->args->args_tab != NULL)
				free_tab((*nodes)->args->args_tab);
		}
		else
			free((*nodes)->fd);
		free((*nodes)->args);
		free(*nodes);
		*nodes = tmp;
	}
	*nodes = NULL;
}

t_node	*ft_create_node(int type)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->type = type;
	if (type == PIPE)
		new->args = NULL;
	else
	{
		new->args = malloc(sizeof(t_args));
		new->args->args_tab = NULL;
		new->args->redir_in = 0;
		new->args->redir_out = 0;
		new->args->infile = 0;
		new->args->outfile = 0;
		new->pid = 1;
		new->fork = 0;
		new->status = 0;
		new->args->infiles = NULL;
		new->args->outfiles = NULL;
	}
	new->left = NULL;
	new->right = NULL;
	return (new);
}

int	ft_node_push_back(t_node **begin_node, int type)
{
	t_node	*new_last_node;
	t_node	*tmp;

	tmp = *begin_node;
	new_last_node = ft_create_node(type);
	if (!new_last_node)
		return (MALLOC_ERR);
	if (!tmp)
		*begin_node = new_last_node;
	else
	{
		while (tmp->right)
			tmp = tmp->right;
		tmp->right = new_last_node;
		new_last_node->left = tmp;
	}
	return (0);
}	
