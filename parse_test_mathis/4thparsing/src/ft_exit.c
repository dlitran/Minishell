/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:12:00 by mafranco          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/17 01:33:21 by mafranco         ###   ########.fr       */
=======
/*   Updated: 2024/03/17 01:30:35 by dlitran          ###   ########.fr       */
>>>>>>> 5507411655a621f0f4015a7837f6dbd0e4bf0808
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

static int	ft_is_numeric(char	*str)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	j = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9')
		&& str[i] != '+' && str[i] != '-' && (str[i] != 32
		|| !(str[i] < 8 || str[i] > 13)))
			return (0);
		if (str[i] == '+' || str[i] == '-')
			j += 1;
		if (str[i] > 47 && str[i] < 58)
			k += 1;
		if (j > 1)
			return (0);
		i++;
	}
	return (k);
}

void	ft_exit(t_data *d, int i)
{
	if (d->cmd->arg[i])
	{
		if (!ft_strncmp(d->cmd->arg[i], "--", 2) && ft_strlen(d->cmd->arg[i]) == 2)
			i++;
		if (!ft_is_numeric(d->cmd->arg[i]))
		{
			g_error = 2;
			ft_putstr_fd(" numeric argument required\n", 2);
			free_commands(d, d->input);
			exit(g_error);
		}
		else
			g_error = ft_atoi(d->cmd->arg[i]);		
	}
	else
		g_error = 0;
	if (d->cmd->nb_arg > 2 && ft_strncmp(d->cmd->arg[1], "--", 2) && ft_strlen(d->cmd->arg[1])== 2)
	{
		ft_putstr_fd(" too many arguments\n", 2);
		g_error = 1;
	}
	free_commands(d, d->input);
	exit(g_error);
}
