/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_args_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <htizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:21:17 by htizi             #+#    #+#             */
/*   Updated: 2022/02/25 02:30:38 by lmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	set_cmd_path(t_node *tmp, char **envp)
{
	char	**path_tab;
	char	*cmd_path;

	path_tab = get_paths_tab(envp);
	find_builtin(&tmp);
	while (tmp)
	{
		cmd_path = NULL;
		if (tmp->type == ARGS && tmp->args->args_tab
			&& tmp->args->is_builtin == NO)
		{
			if (tmp->args->args_tab[0][0])
				cmd_path = get_cmd_path(tmp->args->args_tab[0], path_tab);
			if (cmd_path)
			{
				free(tmp->args->args_tab[0]);
				tmp->args->args_tab[0] = cmd_path;
			}
			else if (tmp->args->args_tab[0][0])
				free(cmd_path);
		}
		tmp = tmp->right;
	}
	free_tab(path_tab);
	return (0);
}

int	fill_args_tab(int counter, t_node *tmp_nodes, t_list **tmp_list)
{
	int	i;

	i = 0;
	if (!counter)
		tmp_nodes->args->args_tab = NULL;
	while (counter)
	{
		tmp_nodes->args->args_tab[i] = ft_strdup((*tmp_list)->value);
		if (!tmp_nodes->args->args_tab[i])
			return (MALLOC_ERR);
		counter--;
		i++;
		*tmp_list = (*tmp_list)->next;
	}
	if (tmp_nodes->args->args_tab)
		tmp_nodes->args->args_tab[i] = NULL;
	return (0);
}

int	count_args(t_list *list)
{
	t_list	*tmp_list;
	int		counter;

	tmp_list = list;
	counter = 0;
	while (tmp_list && tmp_list->type != PIPE)
	{
		counter++;
		tmp_list = tmp_list->next;
	}
	if (tmp_list && tmp_list->type == PIPE)
		tmp_list = tmp_list->next;
	return (counter);
}

int	set_args_tab(t_node **nodes, t_list **list)
{
	t_list	*tmp_list;
	t_node	*tmp_nodes;
	int		counter;

	tmp_list = *list;
	tmp_nodes = *nodes;
	while (tmp_list)
	{
		counter = count_args(tmp_list);
		if (counter)
		{
			tmp_nodes->args->args_tab = malloc(sizeof(char *) * (counter + 1));
			if (!tmp_nodes->args->args_tab)
				return (MALLOC_ERR);
		}
		if (fill_args_tab(counter, tmp_nodes, &tmp_list))
			return (MALLOC_ERR);
		if (tmp_list)
			tmp_list = tmp_list->next;
		if (tmp_nodes->right)
			tmp_nodes = tmp_nodes->right->right;
	}
	if (set_cmd_path(*nodes, g_data.envi) == MALLOC_ERR)
		return (MALLOC_ERR);
	return (0);
}
