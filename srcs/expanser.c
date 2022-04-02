/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 21:50:35 by htizi             #+#    #+#             */
/*   Updated: 2022/02/25 15:03:17 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_not_found(t_list **tmp, t_list **list, char *var_expanded)
{
	if (!(*tmp)->prev)
		lst_delone(tmp, list);
	else
	{
		var_expanded = ft_strdup("\0");
		free ((*tmp)->value);
		(*tmp)->value = var_expanded;
	}
	return (0);
}

int	fetch_var(t_list **tmp, t_list **list)
{
	char	*var_name;
	char	*var_expanded;
	char	*var_check;

	var_expanded = NULL;
	var_name = ms_substr((*tmp)->value, 1, ft_strlen((*tmp)->value) - 1);
	if (!var_name)
		return (MALLOC_ERR);
	var_check = ms_getenv(var_name, g_data.env);
	free (var_name);
	if (!var_check)
		var_not_found(tmp, list, var_expanded);
	else
	{
		var_expanded = ft_strdup(var_check);
		if (!var_expanded)
			return (MALLOC_ERR);
		free ((*tmp)->value);
		(*tmp)->value = var_expanded;
	}
	return (0);
}

int	manage_dollar(t_list **tmp, t_list **list)
{
	int		len;
	char	*last_ret;
	char	*new;

	last_ret = ms_itoa(g_data.last_return);
	len = ft_strlen(last_ret) + (ft_strlen((*tmp)->next->value) - 1);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (MALLOC_ERR);
	ft_strcpy(new, last_ret);
	free(last_ret);
	ft_strcat(new, &(*tmp)->next->value[1]);
	free((*tmp)->next->value);
	(*tmp)->next->value = new;
	lst_delone(tmp, list);
	return (0);
}

int	expand_var(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->type == VAR || tmp->type == VAR + SPACE_FOUND)
		{
			if (fetch_var(&tmp, list))
				return (MALLOC_ERR);
		}
		else if (tmp->next && tmp->value[0] == '$' && (tmp->type == 0
				|| tmp->type == 7) && tmp->next->value[0] == '?')
		{
			if (manage_dollar(&tmp, list))
				return (MALLOC_ERR);
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (0);
}

int	expanser(t_list **list)
{
	int		ret;

	ret = isolate_var_in_list(list);
	if (ret)
		return (ret);
	ret = del_quotes(list);
	if (ret)
		return (ret);
	ret = expand_var(list);
	if (ret)
		return (ret);
	ret = check_syntax(list);
	reset_types(list);
	return (ret);
}
