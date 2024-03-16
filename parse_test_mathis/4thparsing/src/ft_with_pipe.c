/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_with_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:58:12 by dlitran           #+#    #+#             */
/*   Updated: 2024/03/13 01:24:43 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	fd_problem(int nb, int close)
{
	g_error = nb;
	perror("error opening the file\n");
	if (close == 1)
		exit(0);
}

/*
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
	while (d->nb_pipes + 1 - i > 0)
	{
		d->cmd = d->cmd->next;
		i++;
	}
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
*/

void	ft_close_pipes(t_data *d, int pipe_idx)
{
	pipe_idx--;
	while (pipe_idx > 0)
	{
		if (close(d->pipe[pipe_idx][0]) == -1)
			fd_problem(70, 1);
		if (close(d->pipe[pipe_idx - 1][1]) == -1)
			fd_problem(71, 1);
		pipe_idx--;
	}
	if (close(d->pipe[pipe_idx][0]) == -1)
		fd_problem(70, 1);
}

void	ft_process(t_data *d, int i, int order)
{
	int	pipe_idx;
	int	in;
	int	out;

	pipe_idx = i - 1;
	//printf("pipe idx: %i\n", pipe_idx);
	ft_close_pipes(d, pipe_idx);
	if (order == 0)
		pipe_idx++;
	while (i - 1 < d->nb_pipes && order != 0) //No es el primero
	{
		d->cmd = d->cmd->next;
		i++;
	}
	//printf("command: %s\n", d->cmd->exe);
	if (d->cmd->inferior > 0 || d->cmd->inferior_two > 0)
	{
		if (d->cmd->inferior > 0)
		in = open(d->cmd->infile_name, O_RDONLY);
		if (in == -1)
			fd_problem(33, 1);
		if (dup2(in, 0) == -1)
			fd_problem(72, 1);
		if (close (in) == -1)
			fd_problem(73, 1);
		else
			ft_no_pipe_inferior_two(d);
	}
	else if (order != 0) //No es el primero
	{
		if (close(d->pipe[pipe_idx][1]) == -1) //cerramos el write de arriba
			fd_problem(81, 1);
		if (dup2(d->pipe[pipe_idx][0], 0) == -1)
			fd_problem(82, 1);
		if (close(d->pipe[pipe_idx][0]) == -1) //una vez hecho el dup
		fd_problem(81, 1);
	}
	if (d->cmd->superior > 0|| d->cmd->superior_two > 0)
	{
		if (d->cmd->superior > 0)
		{
			out = open(d->cmd->outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (out == -1)
				fd_problem(34, 1);
			if (dup2(out, 1) == -1)
				fd_problem(45, 1);
			if (close(out) == -1)
				fd_problem(46, 1);
		}
		if (d->cmd->superior_two > 0)
		{
			out = open(d->cmd->outfile_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (out == -1)
				fd_problem(35, 1);
			if (dup2(out, 1) == -1)
				fd_problem(47, 1);
			if (close(out) == -1)
				fd_problem(48, 1);
		}
	}
	else if (order != 2) //No ultimo
	{
		if (close(d->pipe[pipe_idx - 1][0]) == -1) //cerramos el read de abajo
			fd_problem(81, 1);
		if (dup2(d->pipe[pipe_idx - 1][1], 1) == -1)
			fd_problem(75, 1);
		if (close(d->pipe[pipe_idx - 1][1]) == -1) //cerramos el read de abajo
			fd_problem(81, 1);
	}
	//printf("lleaga aqui\n");
	ft_exec_funcion(d);
}

