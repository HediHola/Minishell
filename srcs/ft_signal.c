/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <htizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:52:58 by htizi             #+#    #+#             */
/*   Updated: 2022/02/25 16:54:43 by lmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	kill_child(int signal)
{
	kill(g_data.pid, signal);
	if (signal == SIGQUIT)
	{
		ft_putstr_fd("QUIT\n", STDOUT_FILENO);
		g_data.last_return = 131;
	}
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		g_data.last_return = 130;
	}
}

void	handle_sig(void)
{
	signal(SIGTRAP, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGBUS, SIG_DFL);
	signal(SIGABRT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_signal);
}

void	ft_signal(int signal)
{
	if ((signal == SIGINT || signal == SIGQUIT) && g_data.pid != 0)
		kill_child(signal);
	else if (signal == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		g_data.last_return = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	heredoc_handler(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
	rl_on_new_line();
	write(1, "\n", 1);
	g_data.last_return = sig;
}
