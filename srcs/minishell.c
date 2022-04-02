/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauremasson <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 13:46:52 by lauremass         #+#    #+#             */
/*   Updated: 2022/02/25 19:55:02 by lmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_data	g_data;

void	free_minishell(char *line, t_list **list, t_node **nodes)
{
	free(line);
	ft_list_clear(list);
	free_data(&g_data);
	ft_clear_nodes(nodes);
	exit(-1);
}

void	minishell_exec(char *line, t_list **list, t_node **nodes)
{
	if (line[0] != '\0')
		g_data.last_return = lexer(line, list, nodes, g_data.envi);
	if (check_err(&g_data.last_return) && g_data.last_return == MALLOC_ERR)
		free_minishell(line, list, nodes);
}

int	check_ctrl_d_sig(char *line)
{
	if (!line)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	init_main_var(t_main_var *var, char **envp)
{
	var->list = NULL;
	var->nodes = NULL;
	var->line = NULL;
	init_data(envp);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_main_var	var;

	(void)argv;
	(void)argc;
	init_main_var(&var, envp);
	while (g_data.exit_status != 1)
	{
		handle_sig();
		if (isatty(STDIN_FILENO))
			var.line = readline("minishell: ");
		else
		{
			if (get_next_line(STDIN_FILENO, &var.line) == -1)
				break ;
			g_data.exit_status = 1;
		}
		if (check_ctrl_d_sig(var.line))
			break ;
		add_history(var.line);
		minishell_exec(var.line, &var.list, &var.nodes);
		free(var.line);
	}
	free_data(&g_data);
	return (g_data.last_return);
}
