/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <htizi@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:50:07 by user42            #+#    #+#             */
/*   Updated: 2022/02/08 16:45:17 by lauremass        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_elem(t_list **list)
{
	free((*list)->value);
	free(*list);
	*list = NULL;
}

void	ft_list_clear(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (*list != NULL)
	{
		tmp = (*list)->next;
		free((*list)->value);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}

t_list	*ft_create_elem(char *value)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->value = value;
	new->type = type(value);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int	ft_list_push_front(t_list **begin_list, char *value)
{
	t_list	*new_first_elem;
	t_list	*tmp;

	if (!value)
		return (MALLOC_ERR);
	tmp = *begin_list;
	new_first_elem = ft_create_elem(value);
	if (!new_first_elem)
		return (MALLOC_ERR);
	if (!tmp)
		*begin_list = new_first_elem;
	else
	{
		while (tmp->prev)
			tmp = tmp->prev;
		tmp->prev = new_first_elem;
		new_first_elem->next = tmp;
		*begin_list = new_first_elem;
	}
	return (0);
}

int	ft_list_push_back(t_list **begin_list, char *value)
{
	t_list	*new_last_elem;
	t_list	*tmp;

	if (!value)
		return (MALLOC_ERR);
	tmp = *begin_list;
	new_last_elem = ft_create_elem(value);
	if (!new_last_elem)
		return (MALLOC_ERR);
	if (!tmp)
		*begin_list = new_last_elem;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_last_elem;
		new_last_elem->prev = tmp;
	}
	return (0);
}
