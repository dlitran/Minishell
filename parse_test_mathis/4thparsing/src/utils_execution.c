/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:54:38 by dlitran           #+#    #+#             */
/*   Updated: 2024/02/20 23:59:53 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	ft_nb_pipes(t_data *d)
{
	int		nb;
	t_cmd	*a;

	a = d->cmd;
	nb = 0;
	while (a)
	{
		if (a->pipe > 0)
			nb++;
		a = a->next;
	}
	return (nb);
}

int	ft_infile(t_data *d)
{
	t_cmd	*a;

	a = d->cmd;
	while (a)
	{
		if (a->inferior > 0)
		{
			d->infile_name = a->next->exe;
			return (1);
		}
		if (a->inferior_two > 0)
		{
			d->infile_name = a->next->exe;
			return (2);
		}
		a = a->next;
	}
	return (0);
}

int	ft_outfile(t_data *d)
{
	t_cmd	*a;

	a = d->cmd;
	while (a)
	{
		if (a->superior > 0)
		{
			d->outfile_name = a->next->exe;
			return (1);
		}
		if (a->superior_two > 0)
		{
			d->outfile_name = a->next->exe;
			return (2);
		}
		a = a->next;
	}
	return (0);
}
