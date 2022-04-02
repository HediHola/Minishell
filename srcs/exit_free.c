/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauremasson <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:10:41 by lauremass         #+#    #+#             */
/*   Updated: 2022/02/25 02:10:22 by lmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_data(t_data *g_data)
{
	int	i;

	i = 0;
	if (g_data->env != NULL)
		free_env(g_data->env);
	g_data->env = NULL;
	if (g_data->export_env != NULL)
		free_env(g_data->export_env);
	g_data->export_env = NULL;
	free_double_tab(g_data->envi);
}
