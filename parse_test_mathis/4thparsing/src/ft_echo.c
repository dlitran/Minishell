/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:05:34 by mafranco          #+#    #+#             */
/*   Updated: 2024/01/26 22:41:57 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_echo(t_data *d)
{
	int	i;

	i = 1;
	if (d->cmd->nb_arg != 0)
	{
		while (d->cmd->arg[i + 1])
		{
			printf("%s ", d->cmd->arg[i]);
			i++;
		}
		printf("%s", d->cmd->arg[i]);
	}
	printf("\n");
}
