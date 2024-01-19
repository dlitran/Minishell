/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_with_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:58:12 by dlitran           #+#    #+#             */
/*   Updated: 2024/01/19 17:58:12 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_first_process(t_data *d)
{
	int	pipe_idx;
	char	*file;
	int		fd;

	pipe_idx = d->nb_pipes -1;
	if (d->infile == 1)
	{
		file = d->cmd->next->exe;
		fd = open(file, O_RDONLY);
		dup2(fd, 0);
		close (fd);
	}
	/*if (d->infile == 2)
	{
		file = d->cmd->next->exe;
		fd = open(file, );
		dup2(fd, 0);
		close(fd);
	}*/
	close(d->pipe[pipe_idx][0]);
	dup2(d->pipe[pipe_idx][1], 1);
	close(d->pipe[pipe_idx][1]);
	execve(ft_check_path(d->path, d->cmd), d->cmd->arg, d->env);
	exit(0);
}

void	ft_child(t_data *d, int i)
{
	int	pipe_idx;

	pipe_idx = i -1;
	dup2(d->pipe[pipe_idx][0], 0);
	close(d->pipe[pipe_idx][0]);
	dup2(d->pipe[pipe_idx - 1][1], 1);
	close(d->pipe[pipe_idx - 1][1]);
	if (d->infile > 0)
		d->cmd = d->cmd->next;
	while (d->nb_pipes + 1 -i > 0)
	{
		d->cmd = d->cmd->next;
		i++;
	}
	execve(ft_check_path(d->path, d->cmd), d->cmd->arg, d->env);
	exit(0);

}

void	ft_last_process(t_data *d)
{
	int		pipe_idx;
	char	*file;
	int		fd;


	pipe_idx = 0;
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
	if (d->outfile == 1)
	{
		file = d->cmd->next->exe;
		fd = open(file, O_WRONLY | O_CREAT);
		dup2(fd, 1);
		close (fd);
	}
	if (d->outfile == 2)
	{
		file = d->cmd->next->exe;
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND);
		dup2(fd, 1);
		close (fd);
	}
	execve(ft_check_path(d->path, d->cmd), d->cmd->arg, d->env);
	exit (0);
}
