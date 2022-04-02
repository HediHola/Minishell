/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:13:09 by lmasson           #+#    #+#             */
/*   Updated: 2022/02/25 15:06:02 by htizi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_n_option(char **cmds)
{
	int	i;
	int	y;
	int	br;

	i = 1;
	y = 0;
	br = 0;
	while (cmds[i] && cmds[i][y] == '-' && cmds[i][y + 1])
	{
		if (cmds[i][y] != '-')
			return (0);
		y++;
		while (cmds[i][y])
		{
			if (cmds[i][y] != 'n')
				br = -1;
			y++;
		}
		if (br == -1)
			break ;
		i++;
		y = 0;
	}
	return (i);
}

void	echo_option_n(t_args *args, int i)
{
	char	*ret;

	ret = NULL;
	if (args->args_tab[i] == NULL || ft_strcmp(args->args_tab[i], "\n") == 0)
		return ;
	while (args->args_tab[i])
	{
		fd_print(args->args_tab[i], 1);
		if (args->args_tab[i + 1])
			fd_print(" ", 1);
		i++;
	}
}

void	print_lastret(void)
{
	char	*ret;

	ret = NULL;
	ret = ms_itoa(g_data.last_return);
	fd_printnl(ret, 1);
	free(ret);
}

void	echo_no_option(t_args *args, int i)
{
	char	*ret;

	ret = NULL;
	if (args->args_tab[i] == NULL || ft_strcmp(args->args_tab[i], "\n") == 0)
		fd_print("\n", 1);
	else
	{
		while (args->args_tab[i + 1])
		{
			fd_print(args->args_tab[i], 1);
			fd_print(" ", 1);
			i++;
		}
		fd_printnl(args->args_tab[i], 1);
	}
}

int	exec_echo(t_args *args)
{
	int	i;

	i = 1;
	if (args->args_tab[1] != NULL)
		i = check_n_option(args->args_tab);
	if (i > 1)
		echo_option_n(args, i);
	else
		echo_no_option(args, i);
	return (g_data.last_return = COMMAND_WORK);
}
