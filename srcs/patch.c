/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <htizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 20:47:55 by htizi             #+#    #+#             */
/*   Updated: 2022/02/18 23:03:50 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	link_patch(t_list **list, t_list **patch, int pos)
{
	t_list	*tmp_pre_patch;
	t_list	*tmp_post_patch;
	int		tmp_pos;

	tmp_pos = pos;
	tmp_pre_patch = *list;
	while (--pos)
		tmp_pre_patch = tmp_pre_patch->next;
	tmp_post_patch = tmp_pre_patch->next->next;
	tmp_pre_patch->next = *patch;
	(*patch)->prev = tmp_pre_patch;
	while (tmp_pre_patch->next)
		tmp_pre_patch = tmp_pre_patch->next;
	tmp_pre_patch->next = tmp_post_patch;
	if (tmp_post_patch)
		tmp_post_patch->prev = tmp_pre_patch;
}

void	push_patch_front(t_list **list, t_list **patch)
{
	t_list	*tmp_pre_patch;
	t_list	*tmp_post_patch;

	tmp_pre_patch = *list;
	tmp_post_patch = tmp_pre_patch->next;
	*list = *patch;
	tmp_pre_patch = *patch;
	while (tmp_pre_patch->next)
		tmp_pre_patch = tmp_pre_patch->next;
	tmp_pre_patch->next = tmp_post_patch;
	if (tmp_post_patch)
		tmp_post_patch->prev = tmp_pre_patch;
}

char	**create_tab(char *line, int *brackets_unclosed)
{
	char	**tab;
	int		i;
	char	*str;
	int		ret;

	i = 0;
	str = del_quotes_or_brackets(line, 0);
	if (!str)
		return (NULL);
	tab = malloc(sizeof(char *) * (count_lines(str) + 1));
	if (!tab)
		return (NULL);
	ret = fill_tab(tab, str, brackets_unclosed);
	free (str);
	if (*brackets_unclosed == 1)
	{
		free_tab(tab);
		return (NULL);
	}
	if (ret == MALLOC_ERR)
		return (NULL);
	return (tab);
}

t_list	*create_patch(char *line, int *brackets_unclosed, int type)
{
	char	**tab;
	t_list	*patch;
	int		i;

	patch = NULL;
	i = 0;
	tab = create_tab(line, brackets_unclosed);
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		if (ft_list_push_back(&patch, ft_strdup(tab[i])))
			return (NULL);
		i++;
	}
	clear_type(&patch, type);
	free_tab(tab);
	return (patch);
}	

int	patch_list(t_list **list, int pos, int *brackets_unclosed)
{
	t_list	*patch;
	t_list	*tmp_list;
	int		tmp_pos;

	tmp_list = *list;
	tmp_pos = pos;
	while (pos && pos--)
		tmp_list = tmp_list->next;
	patch = create_patch(tmp_list->value, brackets_unclosed, tmp_list->type);
	if (!patch)
		return (MALLOC_ERR);
	if (!tmp_pos)
		push_patch_front(list, &patch);
	else
		link_patch(list, &patch, tmp_pos);
	return (0);
}
