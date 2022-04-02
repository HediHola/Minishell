/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 00:23:01 by lmasson           #+#    #+#             */
/*   Updated: 2022/02/25 02:24:46 by lmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_limit_close(int fd, char *limit)
{
	free(limit);
	close(fd);
}

void	ctrl_d_heredoc(int fd, char *limit)
{
	rl_on_new_line();
	write(1, "\n", 1);
	free_limit_close(fd, limit);
	fd_printnl("The delimiter wasn't the rigth one", STDERR_FILENO);
}

void	ctrl_c_heredoc(int fd, char *limit)
{
	free_limit_close(fd, limit);
	g_data.last_return = 130;
}
