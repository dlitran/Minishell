/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_with_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:58:12 by dlitran           #+#    #+#             */
/*   Updated: 2024/03/16 22:32:04 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	fd_problem(int nb, int close)
{
	g_error = nb;
	ft_putstr_fd("error opening the file\n", 2);
	if (close == 1)
		exit(0);
}

void	ft_close_pipes(t_data *d, int pipe_idx)
{
	pipe_idx--;
	while (1 <= pipe_idx)
	{
		if (close(d->pipe[pipe_idx][0]) == -1)
			fd_problem(70, 1);
		if (close(d->pipe[pipe_idx -1][1]) == -1)
			fd_problem(71, 1);
		pipe_idx--;
	}
}

void	ft_first_process(t_data *d)
{
	int		pipe_idx;

	pipe_idx = d->nb_pipes -1;
	if (d->cmd->inferior > 0)
		ft_in_file_1_process(d, 0);
	if (d->cmd->inferior_two > 0)
		ft_no_pipe_inferior_two(d);
	ft_close_pipes(d, pipe_idx);
	if (close(d->pipe[pipe_idx][0]) == -1)
		fd_problem(74, 1);
	if (dup2(d->pipe[pipe_idx][1], 1) == -1)
		fd_problem(75, 1);
	if (close(d->pipe[pipe_idx][1]) == -1)
		fd_problem(76, 1);
	ft_exec_funcion(d);
}

void	ft_child(t_data *d, int i)
{
	int	pipe_idx;

	pipe_idx = i -1;
	ft_close_pipes(d, pipe_idx);
	if (close(d->pipe[pipe_idx][1]) || close(d->pipe[pipe_idx - 1][0]))
		fd_problem(77, 1);
	if (dup2(d->pipe[pipe_idx][0], 0) == -1)
		fd_problem(78, 1);
	if (close(d->pipe[pipe_idx][0]) == -1)
		fd_problem(79, 1);
	if (dup2(d->pipe[pipe_idx - 1][1], 1) == -1)
		fd_problem(80, 1);
	if (close(d->pipe[pipe_idx - 1][1]) == -1)
		fd_problem(81, 1);
	while (d->nb_pipes + 1 - i > 0)
	{
		d->cmd = d->cmd->next;
		i++;
	}
	ft_exec_funcion(d);
}

void	ft_last_process(t_data *d)
{
	int		pipe_idx;

	pipe_idx = 0;
	ft_close_pipes(d, pipe_idx);
	if (dup2(d->pipe[pipe_idx][0], 0) == -1)
		fd_problem(82, 1);
	if (close(d->pipe[pipe_idx][0]) || close(d->pipe[pipe_idx][1]))
		fd_problem(83, 1);
	while (d->nb_pipes > 0)
	{
		d->cmd = d->cmd->next;
		d->nb_pipes--;
	}
	ft_last_process2(d, NULL, 0);
}
