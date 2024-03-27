/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_with_pipe2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:03:43 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/27 11:43:59 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	with_p3(t_data *d, int pipe_idx)
{
	int	null_fd;
	
	if (close(d->pipe[pipe_idx][0]) == -1)
		fd_problem(108, 1, 1, d);
	if (dup2(d->pipe[pipe_idx][1], 1) == -1)
		fd_problem(109, 1, 2, d);
	if (close(d->pipe[pipe_idx][1]) == -1)
		fd_problem(110, 1, 1, d);
	if (d->cmd->next && d->cmd->next->builtin)
	{
		null_fd = open("/dev/null", O_WRONLY);
		//ft_putstr_fd("fd> \n", 2);
		//ft_putnbr_fd(null_fd, 2);
		dup2(null_fd, 1);
		close(null_fd);
	}
}

void	with_p2(t_data *d, int pipe_idx)
{
	if (d->cmd->superior > 0 || d->cmd->superior_two > 0)
	{
		if (d->cmd->superior > 0)
		{
			if (dup2(d->cmd->out, 1) == -1)
				fd_problem(45, 1, 2, d);
			if (close(d->cmd->out) == -1)
				fd_problem(46, 1, 1, d);
		}
		if (d->cmd->superior_two > 0)
		{
			if (dup2(d->cmd->out, 1) == -1)
				fd_problem(47, 1, 2, d);
			if (close(d->cmd->out) == -1)
				fd_problem(48, 1, 1, d);
		}
	}
	else if (pipe_idx != d->nb_pipes) //hay que dejar el else para el /dev/null
		with_p3(d, pipe_idx);
}

void	with_p1(t_data *d, int pipe_idx)
{
	if (d->cmd->inferior > 0 /*|| d->cmd->inferior_two > 0*/)
	{
		if (d->cmd->inferior > 0)
		{
			if (dup2(d->cmd->in, 0) == -1)
				fd_problem(72, 1, 2, d);
			if (close (d->cmd->in) == -1)
				fd_problem(73, 1, 1, d);
		}
		//else
		//	ft_no_pipe_inferior_two(d);
	}
	else if (pipe_idx != 0) //quito el else
	{
		if (close(d->pipe[pipe_idx -1][1]) == -1)
			fd_problem(81, 1, 1, d);
		if (dup2(d->pipe[pipe_idx -1][0], 0) == -1)
			fd_problem(82, 1, 2, d);
		if (close(d->pipe[pipe_idx -1][0]) == -1)
			fd_problem(107, 1, 1, d);
	}
}
