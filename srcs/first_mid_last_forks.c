/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_mid_last_forks.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <htizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 02:51:48 by htizi             #+#    #+#             */
/*   Updated: 2022/02/26 12:11:31 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup2_firstfork(t_node *tmp)
{
	if (tmp->right)
		close(tmp->right->fd[0]);
	if (tmp->args->infile && tmp->args->infile != -1)
		dup2(tmp->args->infile, STDIN_FILENO);
	if (tmp->args->outfile && tmp->args->outfile != -1)
		dup2(tmp->args->outfile, STDOUT_FILENO);
	else if (tmp->right)
		dup2(tmp->right->fd[1], STDOUT_FILENO);
	if (tmp->right)
		close(tmp->right->fd[1]);
}

int	first_fork(t_node *tmp, char **env, t_node **nodes)
{
	if (tmp->right)
	{
		if (pipe(tmp->right->fd) == -1)
			return (-1);
	}
	tmp->pid = fork();
	g_data.pid = tmp->pid;
	if (tmp->pid == 0)
	{
		dup2_firstfork(tmp);
		if (!tmp->args->is_builtin
			&& execve(tmp->args->args_tab[0], tmp->args->args_tab, env) == -1)
			execve_error(&tmp, nodes);
		else if (tmp->args->is_builtin)
			exec_builtin(tmp->args, nodes);
	}
	if (tmp->right)
		close(tmp->right->fd[1]);
	close_files(&tmp);
	return (0);
}

void	dup2_midfork(t_node *tmp)
{
	if (tmp->right)
		close(tmp->right->fd[0]);
	if (tmp->args->infile && tmp->args->infile != -1)
		dup2(tmp->args->infile, STDIN_FILENO);
	else
		dup2(tmp->left->fd[0], STDIN_FILENO);
	close(tmp->left->fd[0]);
	if (tmp->args->outfile && tmp->args->outfile != -1)
		dup2(tmp->args->outfile, STDOUT_FILENO);
	else
		dup2(tmp->right->fd[1], STDOUT_FILENO);
	if (tmp->right)
		close(tmp->right->fd[1]);
}

int	mid_fork(t_node *tmp, char **env, t_node **nodes)
{
	if (tmp->right)
	{
		if (pipe(tmp->right->fd) == -1)
			return (-1);
	}
	tmp->pid = fork();
	g_data.pid = tmp->pid;
	if (tmp->pid == 0)
	{
		dup2_midfork(tmp);
		if (!tmp->args->is_builtin
			&& execve(tmp->args->args_tab[0], tmp->args->args_tab, env) == -1)
			execve_error(&tmp, nodes);
		else if (tmp->args->is_builtin)
			exec_builtin(tmp->args, nodes);
	}
	close(tmp->left->fd[0]);
	close(tmp->right->fd[1]);
	close_files(&tmp);
	return (0);
}

int	last_fork(t_node *tmp, char **env, t_node **nodes)
{
	tmp->pid = fork();
	g_data.pid = tmp->pid;
	if (tmp->pid == 0)
	{
		if (tmp->args->infile && tmp->args->infile != -1)
			dup2(tmp->args->infile, STDIN_FILENO);
		else
			dup2(tmp->left->fd[0], STDIN_FILENO);
		if (tmp->args->outfile && tmp->args->outfile != -1)
			dup2(tmp->args->outfile, STDOUT_FILENO);
		if (!tmp->args->is_builtin
			&& execve(tmp->args->args_tab[0], tmp->args->args_tab, env) == -1)
			execve_error(&tmp, nodes);
		else if (tmp->args->is_builtin)
			exec_builtin(tmp->args, nodes);
	}
	close(tmp->left->fd[0]);
	close_files(&tmp);
	return (0);
}
