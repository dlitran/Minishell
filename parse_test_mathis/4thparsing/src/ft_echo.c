/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:05:34 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/17 02:03:46 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int	get_flag_echo(t_data *d)
{
	int	i;

	i = 1;
	if (d->cmd->arg[1][0] == '-')
	{
		while (d->cmd->arg[1][i] && d->cmd->arg[1][i] == 'n')
			i++;
		if (!d->cmd->arg[1][i])
			return (1);
	}
	return (0);
}

void	ft_echo(t_data *d)
{
	int	i;
	int	flag;

	if (d->cmd->nb_arg > 1)
	{
		flag = get_flag_echo(d);
		i = 1 + flag;
		if (d->cmd->nb_arg > 1)
		{
			while (i < d->cmd->nb_arg - 1)
			{
				printf("%s ", d->cmd->arg[i]);
				i++;
			}
			if (d->cmd->arg[i])
				printf("%s", d->cmd->arg[i]);
		}
		if (flag == 0)
			printf("\n");
	}
	g_error = 0;
}
