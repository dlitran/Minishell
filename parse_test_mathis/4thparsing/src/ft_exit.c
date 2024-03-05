/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:12:00 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/04 10:58:19 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_exit(t_data *d)
{
	if (d->cmd->arg[1])
		g_error = ft_atoi(d->cmd->arg[1]);
	else
		g_error = 0;
	free_commands(d, d->input);
	exit(g_error);
}
