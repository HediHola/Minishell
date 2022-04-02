/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauremasson <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:38:10 by lauremass         #+#    #+#             */
/*   Updated: 2022/02/25 02:21:20 by lmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	open_outfile(t_args *args)
{
	t_list	*outfile;

	outfile = args->outfiles;
	while (outfile)
	{
		if (outfile->type == SR_REDIRECTION)
			args->outfile = open(outfile->next->value,
					O_RDWR | O_CREAT | O_TRUNC, 0664);
		if (outfile->type == DR_REDIRECTION)
			args->outfile = open(outfile->next->value,
					O_RDWR | O_CREAT | O_APPEND, 0664);
		if (args->outfile == -1)
		{
			fd_print("minishell: ", STDERR_FILENO);
			fd_print(outfile->next->value, STDERR_FILENO);
			fd_print(": ", STDERR_FILENO);
			fd_printnl(strerror(errno), STDERR_FILENO);
			return (g_data.last_return = WRONG_ARG);
		}
		if (outfile->next->next)
			close(args->outfile);
		outfile = outfile->next->next;
	}
	return (g_data.last_return = 0);
}

int	error_open(char *error)
{
	fd_print("minishell: ", STDERR_FILENO);
	fd_print(error, STDERR_FILENO);
	fd_print(": ", STDERR_FILENO);
	fd_printnl("le fichier ou dossier n'existe pas", STDERR_FILENO);
	return (g_data.last_return = WRONG_ARG);
}

int	set_last_ret(int i, char *error)
{
	if (g_data.last_return == 130)
		return (g_data.last_return);
	if (0 < i)
		return (error_open(error));
	return (g_data.last_return = COMMAND_WORK);
}

int	open_infile(t_args *args)
{
	t_list	*infile;
	int		i;
	char	*error;

	infile = args->infiles;
	error = NULL;
	i = 0;
	while (infile)
	{
		if (infile->type == SL_REDIRECTION)
			args->infile = open(infile->next->value, O_RDONLY);
		if (infile->type == DL_REDIRECTION)
			args->infile = here_doc(infile);
		if (g_data.last_return == 130)
			break ;
		if (args->infile == -1 && ++i == 1)
			error = infile->next->value;
		else if (infile->next->next)
			close(args->infile);
		infile = infile->next->next;
	}
	return (set_last_ret(i, error));
}

int	open_file(t_node **node)
{
	t_node	*n;
	t_args	*args;
	int		ret;
	int		i;

	n = *node;
	ret = 0;
	args = n->args;
	if (n->type != PIPE)
	{
		if (args->infiles)
		{
			i = open_infile(args);
			if (i == WRONG_ARG)
				return (ret = 1);
			else if (i == 130)
				return (ret = 130);
		}
		if (args->outfiles)
			open_outfile(args);
	}
	return (ret);
}
