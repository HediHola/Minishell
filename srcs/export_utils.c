/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauremasson <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 12:08:30 by lauremass         #+#    #+#             */
/*   Updated: 2022/02/24 19:07:26 by lauremass        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_digit(char c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

int	is_alpha(char c)
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
		return (1);
	return (0);
}

int	check_format(char *args)
{
	int	i;

	i = 0;
	if (is_digit(args[i]))
		return (0);
	while (args[i])
	{
		if (!is_digit(args[i]) && !is_alpha(args[i])
			&& args[i] != '\'' && args[i] != '\"' && args[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_key(char *args, enum e_builtin cmd)
{
	if (!check_format(args))
	{
		if (cmd == EXPORT)
			fd_print("minishell: export: \"", 1);
		else
			fd_print("minishell: unset: \"", 1);
		fd_print(args, 1);
		fd_printnl("\" identifiant non valable", 1);
		return (0);
	}
	return (1);
}
