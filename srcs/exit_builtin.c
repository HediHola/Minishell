/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauremasson <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 03:04:19 by lauremass         #+#    #+#             */
/*   Updated: 2022/02/25 16:39:44 by lmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

unsigned long long	ms_atoi_exit(char *nbr)
{
	unsigned long long	num;
	int					i;

	i = 0;
	num = 0;
	while (nbr[i] && ((9 <= nbr[i] && nbr[i] <= 13) || nbr[i] == 32))
		i++;
	if (nbr[i] == '-' || nbr[i] == '+')
		i++;
	while (nbr[i])
	{
		num = num * 10 + (nbr[i] - '0');
		i++;
	}
	return (num);
}

int	atoi_exit(char *nbr)
{
	int					num;
	int					i;
	int					sign;

	i = 0;
	num = 0;
	sign = 1;
	while (nbr[i] && ((9 <= nbr[i] && nbr[i] <= 13) || nbr[i] == 32))
		i++;
	if (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nbr[i])
	{
		num = num * 10 + (nbr[i] - '0');
		i++;
	}
	return (num * sign);
}

int	is_num(char *nbr)
{
	int	i;

	i = 0;
	if (nbr[i] == '-')
		i++;
	while (nbr[i])
	{
		if (!('0' <= nbr[i] && nbr[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	check_arg_exit(t_args *args)
{
	if (!is_num(args->args_tab[1])
		|| ms_atoi_exit(args->args_tab[1]) > 9223372036854775807
		& ft_strcmp("-922337236854775808", args->args_tab[1]) != 0)
		return (0);
	return (1);
}

int	exec_exit(t_args *args)
{
	if (!args->nb_pipes)
		fd_printnl("exit", 2);
	if (args->args_tab[1] != NULL && args->args_tab[2] != NULL)
	{
		fd_printnl("minishell: exit: too many arguments", 2);
		g_data.last_return = 1;
	}
	else if (args->args_tab[1] != NULL)
	{
		g_data.exit_status = 1;
		if (check_arg_exit(args) == 0)
		{
			fd_printnl("minishell: exit: numeric argument required", 2);
			g_data.last_return = 2;
		}
		else
		{
			g_data.last_return = (unsigned char)atoi_exit(args->args_tab[1])
				% 256;
			g_data.exit_status = 1;
		}
	}
	else
		g_data.exit_status = 1;
	return (g_data.last_return);
}
