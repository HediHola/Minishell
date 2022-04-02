/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <htizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 21:14:16 by htizi             #+#    #+#             */
/*   Updated: 2022/02/15 21:14:36 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_shlvl(char *cmd)
{
	char	*slash;

	slash = ft_strchr(cmd, '/');
	while (slash)
	{
		cmd = slash + 1;
		slash = ft_strchr(slash + 1, '/');
	}
	if (!ft_strcmp(cmd, "minishell"))
		return (1);
	return (0);
}
