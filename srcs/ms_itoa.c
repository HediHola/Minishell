/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:27:10 by lmasson           #+#    #+#             */
/*   Updated: 2022/02/06 14:08:08 by lauremass        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	len_number(int nbr, int base_len)
{
	int	nbr_len;

	nbr_len = 0;
	if (nbr < 0)
	{
		nbr = (-1) * nbr;
		nbr_len++;
	}
	while (0 < nbr)
	{
		nbr = nbr / base_len;
		nbr_len++;
	}
	return (nbr_len);
}

char	*ms_itoa(int nbr)
{
	int		nbr_len;
	char	*str;
	int		i;

	nbr_len = len_number(nbr, 10);
	i = nbr_len;
	if (nbr == 0)
		return (ft_strdup("0"));
	str = malloc(sizeof(int) * (nbr_len + 1));
	if (!str)
		return (NULL);
	if (nbr < 0)
	{
		nbr = (-1) * nbr;
		str[0] = '-';
	}
	str[i--] = '\0';
	while (0 < nbr)
	{
		str[i--] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	return (str);
}
