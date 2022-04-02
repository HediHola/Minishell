/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauremasson <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 08:05:46 by lauremass         #+#    #+#             */
/*   Updated: 2022/02/25 20:39:49 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_path(char *path)
{
	int		chdir_return;
	char	save[PATH_MAX];
	char	new_pwd[PATH_MAX];
	char	*old_pwd;

	chdir_return = 0;
	getcwd(save, PATH_MAX);
	chdir_return = chdir(path);
	if (chdir_return == -1)
	{
		fd_print("cd: ", STDERR_FILENO);
		fd_print(strerror(errno), STDERR_FILENO);
		fd_print(" ", STDERR_FILENO);
		fd_printnl(path, STDERR_FILENO);
		return (g_data.last_return = WRONG_ARG);
	}
	old_pwd = ms_getenv("PWD", g_data.env);
	if (old_pwd == NULL)
		execute_export("OLDPWD", save, F_TRUNC);
	else
		execute_export("OLDPWD", old_pwd, F_TRUNC);
	getcwd(new_pwd, PATH_MAX);
	execute_export("PWD", new_pwd, F_TRUNC);
	return (g_data.last_return = COMMAND_WORK);
}

int	exec_cd_home(t_args *args)
{
	char	*home;

	(void)args;
	home = ms_getenv("HOME", g_data.env);
	if (home == NULL)
	{
		fd_printnl("minishell: HOME path is not set", STDERR_FILENO);
		return (g_data.last_return = WRONG_ARG);
	}
	exec_path(home);
	return (g_data.last_return = COMMAND_WORK);
}

int	exec_oldpath(t_args *args)
{
	char	*old_pwd;

	(void)args;
	old_pwd = ms_getenv("OLDPWD", g_data.env);
	if (old_pwd == NULL)
	{
		fd_printnl("minishell: OLDPWD path is not set", STDERR_FILENO);
		return (g_data.last_return = WRONG_ARG);
	}
	fd_printnl(old_pwd, 1);
	exec_path(old_pwd);
	return (g_data.last_return = COMMAND_WORK);
}

int	exec_cd(t_args *args)
{
	char	*save;

	save = NULL;
	if (args->args_tab[1] == NULL)
		exec_cd_home(args);
	else
	{
		if (ft_strcmp("-", args->args_tab[1]) == 0)
			exec_oldpath(args);
		else if (ft_strcmp("~", args->args_tab[1]) == 0)
			exec_cd_home(args);
		else
			exec_path(args->args_tab[1]);
		return (g_data.last_return);
	}
	return (g_data.last_return);
}
