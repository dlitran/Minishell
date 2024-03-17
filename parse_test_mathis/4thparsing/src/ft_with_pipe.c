/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_with_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:58:12 by dlitran           #+#    #+#             */
/*   Updated: 2024/03/17 20:09:06 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	fd_problem(int nb, int close, int code, t_data *d)
{
	if (d->f_err == 0)
	{
		g_error = nb;
		if (code == 1)
			ft_putstr_fd("close error\n", 2);
		if (code == 2)
			ft_putstr_fd("dup error\n", 2);
	}
	if (close == 1)
		exit(0);
}

void	ft_close_pipes(t_data *d, int pipe_idx)
{
	pipe_idx--;
	while (1 <= pipe_idx)
	{
		if (close(d->pipe[pipe_idx][0]) == -1)
			fd_problem(70, 1, 1, d);
		if (close(d->pipe[pipe_idx -1][1]) == -1)
			fd_problem(71, 1, 1, d);
		pipe_idx--;
	}
}

void	ft_process(t_data *d, int i, int order)
{
	int	pipe_idx;

	pipe_idx = i - 1;
	if (order == 0)
		pipe_idx++;
	while (i - 1 < d->nb_pipes && order != 0)
	{
		d->cmd = d->cmd->next;
		i++;
	}
	with_p1(d, order, pipe_idx);
	with_p2(d, order, pipe_idx);
	ft_exec_funcion(d);
}
