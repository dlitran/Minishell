/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:07:22 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/21 00:46:21 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_pwd(t_data *d)
{
	int	i;

	i = 0;
	if (d->cmd->nb_arg == 1)
	{
		while (d->env[i] && ft_strncmp(d->env[i], "PWD=", 4) != 0)
			i++;
		if (d->env[i])
		{
			printf("%s\n", (d->env[i] + 4));
			g_error = 0;
		}
		else
			g_error = 53;
	}
	else
	{
		perror("pwd: too many arguments\n");
		g_error = 52;
	}
}
