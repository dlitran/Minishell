/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 00:51:06 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/17 19:32:25 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int	ut_export(t_data *d, int i)
{
	if (d->cmd->nb_arg == 1)
		return (1);
	if (d->cmd->arg[i][0] == '-')
	{
		err_less();
		return (1);
	}
	if (ft_valid_identifier(d->cmd->arg, 1, 1))
		return (1);
	return (0);
}

void	err_less(void)
{
	ft_putstr_fd(" invalid option\n", 2);
	g_error = 2;
}

int	prt_err(char *str, int err)
{
	if (err == 1)
		ft_putstr_fd("export: '", 2);
	else
		ft_putstr_fd("unset: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_error = 1;
	return (1);
}
