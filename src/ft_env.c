/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:10:47 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/17 17:06:50 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

static void	ft_env_export2(char *env, int j)
{
	printf("=");
	j += 1;
	printf("\"");
	while (env[j])
	{
		printf("%c", env[j]);
		j++;
	}
	printf("\"\n");
}

void	ft_env_export(t_data *d)
{
	int	i;
	int	j;

	i = 0;
	while (d->env[i])
	{
		j = 0;
		printf("declare -x ");
		while (d->env[i][j] != '=')
		{
			printf("%c", d->env[i][j]);
			j++;
		}
		ft_env_export2(d->env[i], j);
		i++;
	}
	g_error = 0;
}

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
		g_error = 0;
	}
	else
	{
		perror("env: too manny arguments\n");
		g_error = 52;
	}
}
