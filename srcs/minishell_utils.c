/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htizi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:30:08 by htizi             #+#    #+#             */
/*   Updated: 2022/02/25 16:07:15 by lmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_err(int *ret)
{
	if (*ret == MALLOC_ERR)
	{
		ft_putstr_fd("minishell: malloc error\n", STDERR_FILENO);
		return (1);
	}
	if (*ret == QUOTES_UNCLOSED)
	{
		ft_putstr_fd("minishell: quotes unclosed\n", STDERR_FILENO);
		*ret = 2;
		return (2);
	}
	if (*ret == SYNTAX_ERR)
	{
		ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
		*ret = 2;
		return (2);
	}
	return (0);
}

int	closed_quotes(char *line)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 1;
	d_quote = 1;
	while (line[i])
	{
		if (line[i] == '\'' && d_quote == 1)
			s_quote *= -1;
		if (line[i] == '\"' && s_quote == 1)
			d_quote *= -1;
		i++;
	}
	if (s_quote < 0 || d_quote < 0)
		return (QUOTES_UNCLOSED);
	return (0);
}

int	lexer(char *line, t_list **list, t_node **nodes, char **env)
{
	int		ret;

	(void)env;
	if (closed_quotes(line))
		return (QUOTES_UNCLOSED);
	if (create_list(list, line))
		return (MALLOC_ERR);
	ret = expanser(list);
	if (ret)
	{
		ft_list_clear(list);
		return (ret);
	}
	ret = parser(list, nodes);
	if (g_data.last_return == 130)
		g_data.last_return = 0;
	ft_list_clear(list);
	if (ret)
		return (ret);
	ret = forking_loop(nodes, env);
	ft_clear_nodes(nodes);
	return (ret);
}
