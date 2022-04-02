/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauremasson <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:21:28 by lauremass         #+#    #+#             */
/*   Updated: 2022/02/25 19:53:32 by lmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	create_heredoc(void)
{
	int	fd;

	fd = open(HEREDOC, O_WRONLY | O_TRUNC | O_CREAT, 0600);
	if (fd == -1)
	{
		fd_print("minishell: heredoc: ", STDERR_FILENO);
		fd_printnl(strerror(errno), STDERR_FILENO);
		return (g_data.last_return = WRONG_ARG);
	}
	return (fd);
}

int	treat_line(char *line, char *limit, int fd)
{
	if (line == NULL && g_data.last_return == SIGINT)
	{
		ctrl_c_heredoc(fd, limit);
		return (0);
	}
	else if (line == NULL)
	{
		ctrl_d_heredoc(fd, limit);
		return (0);
	}
	if (!line)
		line = ft_strdup("");
	if (ft_strcmp(line, limit) == 0)
	{
		free_limit_close(fd, limit);
		free(line);
		return (0);
	}
	else
		fd_printnl(line, fd);
	free(line);
	return (1);
}

void	exec_heredoc(int fd, t_list *infile)
{
	char	*limit;
	char	*line;
	int		ret;

	limit = ft_strdup(infile->next->value);
	ret = 1;
	while (ret)
	{
		line = readline("> ");
		ret = treat_line(line, limit, fd);
	}
}

int	here_doc(t_list *infile)
{
	int		fd;
	int		save;

	save = dup(STDIN_FILENO);
	signal(SIGINT, &heredoc_handler);
	fd = create_heredoc();
	if (fd == -1)
		return (g_data.last_return = WRONG_ARG);
	exec_heredoc(fd, infile);
	dup2(save, STDIN_FILENO);
	close(save);
	fd = open(HEREDOC, O_RDONLY);
	unlink(HEREDOC);
	return (fd);
}
