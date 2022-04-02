/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 10:57:12 by lmasson           #+#    #+#             */
/*   Updated: 2022/02/24 21:06:18 by lmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_next(char *buffer, int *next, int *end_of_line, int i)
{
	if (!buffer[i])
	{
		*next = 0;
		*end_of_line = 0;
	}
	else
	{
		*next = i + 1;
		*end_of_line = 1;
	}
}

int	begin(char **line, char *buffer, int *next_call_line, int *end_of_line)
{
	int		i;

	i = 0;
	while (buffer[*next_call_line + i] && buffer[*next_call_line + i] != '\n')
		i++;
	*line = (char *)malloc(sizeof(char) * (i + 1));
	if (!(*line))
		return (0);
	**line = '\0';
	ft_strncat(*line, buffer + *next_call_line, i);
	manage_next(buffer, next_call_line, end_of_line, *next_call_line + i);
	return (1);
}

int	manage_line(char **line, char *buffer, int *next, int *end_of_line)
{
	int		i;
	int		len_line;
	char	*temp;

	i = 0;
	len_line = 0;
	if (*line != NULL)
		len_line = ft_strlen(*line);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	temp = (char *)malloc(sizeof(char) * (i + len_line + 1));
	if (!temp)
		return (0);
	*temp = '\0';
	if (*line)
	{
		ft_strcpy(temp, *line);
		free(*line);
	}
	*line = ft_strncat(temp, buffer, i);
	manage_next(buffer, next, end_of_line, i);
	return (1);
}

int	check_line(char *line, int len)
{
	int	i;

	i = 0;
	if (len == -1)
		return (0);
	while (i < len - 1)
	{
		if ((0 <= line[i] && line[i] <= 31) || line[i] == 127)
			return (0);
		i++;
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	buffer[BUFFER_SIZE + 1] = "";
	static int	next_call_line = 0;
	static int	end_of_file = 0;
	int			read_return;
	int			end_of_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	*line = NULL;
	read_return = 1;
	end_of_line = 0;
	if (next_call_line != 0)
		if (!begin(line, buffer, &next_call_line, &end_of_line))
			return (-1);
	while (read_return != 0 && !end_of_line)
	{
		read_return = read(fd, buffer, BUFFER_SIZE);
		if (!check_line(buffer, read_return))
			return (-1);
		buffer[read_return] = '\0';
		if (!(manage_line(line, buffer, &next_call_line, &end_of_line)))
			return (-1);
		end_of_file = read_return == 0;
	}
	return (!(end_of_file && next_call_line == 0));
}
