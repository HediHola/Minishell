/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:58:24 by lmasson           #+#    #+#             */
/*   Updated: 2022/02/25 20:30:19 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	find_builtin(t_node **node)
{
	t_node	*define;

	define = *node;
	while (define)
	{
		if (define->args != NULL)
			define->args->is_builtin = 0;
		if (define->args != NULL && define->args->args_tab != NULL)
			define->args->is_builtin = is_builtin(define->args->args_tab[0]);
		define = define->right;
	}
	return (0);
}

enum e_builtin	type_builtin(int i)
{
	if (i == 0)
		return (ECHO);
	if (i == 1)
		return (CD);
	if (i == 2)
		return (PWD);
	if (i == 3)
		return (EXPORT);
	if (i == 4)
		return (UNSET);
	if (i == 5)
		return (ENV);
	if (i == 6)
		return (EXIT);
	return (NO);
}

enum e_builtin	is_builtin(char	*cmd)
{
	char	**builtin;
	int		i;

	builtin = (char *[8]){"echo", "cd", "pwd", "export",
		"unset", "env", "exit"};
	i = 0;
	while (builtin[i])
	{
		if (ft_strcmp(cmd, builtin[i]) == 0)
			return (type_builtin(i));
		i++;
	}
	return (NO);
}

int	exec_builtin(t_args *args, t_node **nodes)
{
	if (args->is_builtin == ECHO)
		exec_echo(args);
	else if (args->is_builtin == CD)
		exec_cd(args);
	else if (args->is_builtin == PWD)
		exec_pwd(args);
	else if (args->is_builtin == EXPORT)
		exec_export(args);
	else if (args->is_builtin == UNSET)
		exec_unset(args);
	else if (args->is_builtin == ENV)
		exec_env(g_data.env, args->is_builtin);
	else if (args->is_builtin == EXIT)
		exec_exit(args);
	if (args->is_builtin != NO
		&& (args->redir_in || args->redir_out || args->nb_pipes))
	{
		while ((*nodes)->left)
			*nodes = (*nodes)->left;
		ft_clear_nodes(nodes);
		free_data(&g_data);
		exit (g_data.last_return);
	}
	return (0);
}
