/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:30:02 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/15 09:40:53 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	free_all_pipe(int **pipe, int i, int err, int nb)
{
	while (i > 0)
	{
		i--;
		free(pipe[i]);
	}
	free(pipe);
	if (err == 1)
	{
		perror("error allocating memory for pipes\n");
		g_error = nb;
	}
	if (err == 2)
	{
		perror("error fork\n");
		g_error = nb;
	}
}

void	ft_call_process(t_data *d)
{
	int	i;

	i = 1;
	while (i < d->nb_pipes + 1 && d->pid[i - 1] == 0)
	{
		pipe(d->pipe[i - 1]);
		d->pid[i] = fork ();
		i++;
	}
	i--;
	if (d->pid[i] == -1)
	{
		v_err_msg("error pid\n", 32);
		exit(0);
	}
	if (i == d->nb_pipes && d->pid[i] == 0)
		ft_first_process(d);
	else if (i == 1)
		ft_last_process(d);
	else
		ft_child(d, i);
	exit(g_error);
}

void	ft_exec_pipe(t_data *d, int i)
{
	d->pipe = malloc(sizeof(int *) * d->nb_pipes);
	if (!d->pipe)
		return (v_err_msg("error allocating memory for d->pipe\n", 29));
	while (i < d->nb_pipes)
	{
		d->pipe[i] = malloc(sizeof(int) * 2);
		if (!d->pipe[i])
			return (free_all_pipe(d->pipe, i, 1, 30));
		i++;
	}
	d->pid = malloc(sizeof(pid_t) * (d->nb_pipes + 1));
	if (!d->pid)
		return (free_all_pipe(d->pipe, i, 1, 31));
	d->pid[0] = fork();
	if (d->pid[0] == -1)
		return (free_all_pipe(d->pipe, i, 2, 35));
	else if (d->pid[0] == 0)
		ft_call_process(d);
	waitpid(d->pid[0], &g_error, 0);
	if (g_error == 256 || g_error == 512)
		g_error = g_error / 256;
	free(d->pid);
	free_all_pipe(d->pipe, i, 0, 0);
	return ;
}
