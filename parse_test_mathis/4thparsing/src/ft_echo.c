/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:05:34 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/03 21:43:34 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_echo(t_data *d)
{
	int	i;
	int	flag;

	if (d->cmd->arg[1] && ft_strncmp(d->cmd->arg[1], "-n", 2) == 0)
		flag = 1;
	else
		flag = 0;
	i = flag + 1;
	if (d->cmd->nb_arg != 0)
	{
		while (d->cmd->arg[i + 1])
		{
			printf("%s ", d->cmd->arg[i]);
			i++;
		}
		if (d->cmd->arg[i])
			printf("%s", d->cmd->arg[i]);
	}
	if (flag == 0)
		printf("\n");
	g_error = 0;
}
