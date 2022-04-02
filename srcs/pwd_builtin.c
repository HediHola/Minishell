/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:42:50 by lmasson           #+#    #+#             */
/*   Updated: 2022/02/25 02:29:49 by lmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_pwd(t_args *args)
{
	char	*pwd;
	char	*current_pwd;

	(void)args;
	pwd = ms_getenv("PWD", g_data.env);
	if (pwd == NULL)
		current_pwd = getcwd(NULL, 0);
	else
		current_pwd = ft_strdup(pwd);
	fd_printnl(current_pwd, 1);
	free(current_pwd);
	g_data.last_return = COMMAND_WORK;
	return (0);
}
