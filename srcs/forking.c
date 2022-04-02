/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 11:16:20 by htizi             #+#    #+#             */
/*   Updated: 2022/02/26 11:16:24 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_files(t_node **nodes)
{
	t_node	*tmp;

	tmp = *nodes;
	if (tmp->args->infile && tmp->args->infile != -1)
	{
		close(tmp->args->infile);
		tmp->args->infile = 0;
	}
	if (tmp->args->outfile && tmp->args->outfile != -1)
	{
		close(tmp->args->outfile);
		tmp->args->outfile = 0;
	}
	return (0);
}

int	wait_childs(t_node **nodes)
{
	t_node	*tmp;
	int		ret;

	tmp = *nodes;
	ret = 0;
	while (tmp)
	{
		if (tmp->type == ARGS && tmp->fork)
		{
			waitpid(tmp->pid, &tmp->status, 0);
			if (WIFEXITED(tmp->status))
				g_data.last_return = WEXITSTATUS(tmp->status);
		}
		tmp = tmp->right;
	}
	return (g_data.last_return);
}

int	launch_fork(t_node *tmp, char **env, t_node **nodes)
{
	int		ret;

	ret = 0;
	if (!tmp->left && tmp->args->args_tab)
		ret = first_fork(tmp, env, nodes);
	else if (tmp->left && tmp->right && tmp->args->args_tab)
		ret = mid_fork(tmp, env, nodes);
	else if (!tmp->right && tmp->args->args_tab)
		ret = last_fork(tmp, env, nodes);
	else
	{
		if (tmp->right)
			close(tmp->right->fd[1]);
		close_files(&tmp);
	}
	return (ret);
}

int	forking(t_node *tmp, char **env, t_node **nodes)
{
	int		ret;

	ret = 0;
	if (open_file(&tmp))
	{
		if (tmp->right)
			close(tmp->right->fd[1]);
		return (-1);
	}
	signal(SIGQUIT, ft_signal);
	if (tmp->args->args_tab && ft_shlvl(tmp->args->args_tab[0]))
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (tmp->args->is_builtin && !tmp->args->redir_in
		&& !tmp->args->redir_out && !tmp->args->nb_pipes)
	{
		exec_builtin(tmp->args, nodes);
		return (g_data.last_return);
	}
	else
		ret = launch_fork(tmp, env, nodes);
	return (ret);
}

int	forking_loop(t_node **nodes, char **env)
{
	t_node	*tmp;
	int		ret;

	tmp = *nodes;
	ret = 0;
	while (tmp)
	{
		if (tmp->type == ARGS)
		{
			ret = forking(tmp, env, nodes);
			if (ret == 0)
				tmp->fork = 1;
			if (ret == -1)
				break ;
			if (ret == MALLOC_ERR)
				return (ret);
		}
		tmp = tmp->right;
	}
	wait_childs(nodes);
	g_data.pid = 0;
	return (g_data.last_return);
}
