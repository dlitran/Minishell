/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:12:00 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/16 11:19:41 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

static int	ft_is_numeric(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9')
		&& str[i] != '+' && str[i] != '-' && (str[i] != 32
		|| !(str[i] < 8 || str[i] > 13)))
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_data *d)
{
	if (d->cmd->nb_arg > 2)
		g_error = 1;
	else if (d->cmd->arg[1])
	{
		if (ft_is_numeric(d->cmd->arg[1]))
			g_error = 2;
		else
			g_error = ft_atoi(d->cmd->arg[1]);
	}
	else
		g_error = 0;
	free_commands(d, d->input);
	exit(g_error);
}
