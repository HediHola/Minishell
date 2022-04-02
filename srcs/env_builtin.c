/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauremasson <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 02:27:49 by lauremass         #+#    #+#             */
/*   Updated: 2022/02/25 02:40:40 by lmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_env(t_env *env, enum e_builtin type)
{
	t_env	*print;

	print = env;
	while (print != NULL)
	{
		if (type == EXPORT)
			fd_print("export ", 1);
		fd_print(print->key, 1);
		fd_print("=", 1);
		if (type == EXPORT)
		{
			fd_print("\"", 1);
			fd_print(print->content, 1);
			fd_printnl("\"", 1);
		}
		else
			fd_printnl(print->content, 1);
		print = print->next;
	}
	return (g_data.last_return = COMMAND_WORK);
}
