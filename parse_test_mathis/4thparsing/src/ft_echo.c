/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:05:34 by mafranco          #+#    #+#             */
/*   Updated: 2024/01/20 14:12:40 by mafranco         ###   ########.fr       */
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
