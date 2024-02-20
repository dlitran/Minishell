/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:10:47 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/20 17:59:20 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_env(t_data *d)
{
	int	i;

	i = 0;
	if (d->cmd->nb_arg == 1)
	{
		while (d->env[i])
		{
			printf("%s\n", d->env[i]);
			i++;
		}
	}
	else
		printf("env: too manny arguments\n");
	nb_error = 0;
}
