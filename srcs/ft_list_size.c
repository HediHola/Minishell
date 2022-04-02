/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <htizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 18:23:10 by htizi             #+#    #+#             */
/*   Updated: 2021/12/27 19:15:26 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_list_size(t_list *begin_list)
{
	int		n;

	n = 0;
	while (begin_list)
	{
		n++;
		begin_list = begin_list->next;
	}
	return (n);
}
