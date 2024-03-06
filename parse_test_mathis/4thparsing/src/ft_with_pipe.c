/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_with_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:58:12 by dlitran           #+#    #+#             */
/*   Updated: 2024/02/21 01:13:33 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	fd_problem(int nb, int close)
{
	g_error = nb;
	perror("error opening the file\n");
	if (close == 1)
		exit(0);
}

void	ft_close_pipes(t_data *d, int pipe_idx)
{
	pipe_idx--;
	while (1 <= pipe_idx)
	{
		close(d->pipe[pipe_idx][0]);
		close(d->pipe[pipe_idx -1][1]);
		pipe_idx--;
	}
	//close(d->pipe[pipe_idx][0]);
}

void	ft_first_process(t_data *d)
{
	int		pipe_idx;
	char	*file;
	int		fd;

	pipe_idx = d->nb_pipes -1;
	if (d->infile == 1)
	{
		file = d->infile_name;
		fd = open(file, O_RDONLY);
		if (fd == -1)
			fd_problem(33, 1);
		dup2(fd, 0);
		close (fd);
	}
	if (d->infile == 2)
		ft_no_pipe_inferior_two(d);
	ft_close_pipes(d, pipe_idx);
	close(d->pipe[pipe_idx][0]);
	dup2(d->pipe[pipe_idx][1], 1);
	close(d->pipe[pipe_idx][1]);
	ft_exec_funcion(d);
}

void	ft_child(t_data *d, int i)
{
	int	pipe_idx;

	pipe_idx = i -1;

	ft_close_pipes(d, pipe_idx);
	close(d->pipe[pipe_idx][1]);
	close(d->pipe[pipe_idx - 1][0]); //los que
	dup2(d->pipe[pipe_idx][0], 0);
	close(d->pipe[pipe_idx][0]);
	dup2(d->pipe[pipe_idx - 1][1], 1);
	close(d->pipe[pipe_idx - 1][1]);
	if (d->infile > 0)
		d->cmd = d->cmd->next;
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
	dup2(d->pipe[pipe_idx][0], 0);
	close(d->pipe[pipe_idx][0]);
	close(d->pipe[pipe_idx][1]);
	if (d->infile > 0)
		d->cmd = d->cmd->next;
	while (d->nb_pipes > 0)
	{
		d->cmd = d->cmd->next;
		d->nb_pipes--;
	}
	ft_last_process2(d, NULL, 0);
}
