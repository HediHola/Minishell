/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attribute_and_clear_type.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <htizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 05:44:25 by htizi             #+#    #+#             */
/*   Updated: 2022/02/06 12:59:48 by lauremass        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_type(t_list **patch, int type)
{
	t_list	*tmp;

	tmp = *patch;
	while (tmp)
	{
		if (tmp->type != VAR)
			tmp->type = DISPLAY_ONLY;
		if (!tmp->next)
			tmp->type += type;
		tmp = tmp->next;
	}
}

int	type(char *value)
{
	if (value[0] == '<' && value[1] == '<')
		return (DL_REDIRECTION);
	if (value[0] == '<')
		return (SL_REDIRECTION);
	if (value[0] == '>' && value[1] == '>')
		return (DR_REDIRECTION);
	if (value[0] == '>')
		return (SR_REDIRECTION);
	if (value[0] == '|')
		return (PIPE);
	if (value[0] == '$' && value[1])
		return (VAR);
	return (WORD);
}
