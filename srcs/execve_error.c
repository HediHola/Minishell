/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <htizi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 23:53:05 by htizi             #+#    #+#             */
/*   Updated: 2022/02/25 02:09:38 by lmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != c)
		s++;
	if (*s == c || c == '\0')
		return ((char *)s);
	return (NULL);
}

void	cmd_not_found(char *s)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd(" : command not found\n", STDERR_FILENO);
}

int	execve_error(t_node **tmp, t_node **nodes)
{
	int		ret;
	int		fd;
	char	*s;

	s = (*tmp)->args->args_tab[0];
	ret = 127;
	if (ft_strchr(s, '/') && ft_strcmp(s, ""))
	{
		fd = open(s, O_DIRECTORY);
		if (fd != -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(s, STDERR_FILENO);
			ft_putstr_fd(" : is a directory\n", STDERR_FILENO);
			ret = 126;
		}
		else
			perror("minishell");
	}
	else
		cmd_not_found(s);
	ft_clear_nodes(nodes);
	free_data(&g_data);
	exit(ret);
}
