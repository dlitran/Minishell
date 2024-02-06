/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:30:02 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/03 15:00:49 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	free_all_pipe(int **pipe, int i, int err)
{
	while (i > 0)
	{
		i--;
		free(pipe[i]);
	}
	free(pipe);
	if (err == 1)
		printf("Error allocating memory for pipes\n");
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
		printf("Error fork num: %d\n", i);
		exit(0);
	}
	else if (d->pid[i] != 0)
		waitpid(d->pid[i], NULL, 0);
	if (i == d->nb_pipes && d->pid[i] == 0)
		ft_first_process(d); // ejecuta pipe + 1
	else if (i == 1)
		ft_last_process(d); // ejecuta pipe 0
	else
		ft_child(d, i); // ejecuta pipes + 1 - 
	exit(0);
}

void	ft_exec_pipe(t_data *d, int i)
{
	d->pipe = malloc(sizeof(int *) * d->nb_pipes);
	while (i < d->nb_pipes)
	{
		d->pipe[i] = malloc(sizeof(int) * 2); //cada pipe tiene 2 extremos.
		if (!d->pipe[i])
			return (free_all_pipe(d->pipe, i, 1));
		i++;
	}
	d->pid = malloc(sizeof(pid_t) * (d->nb_pipes + 1));
	if (!d->pid)
		return (free_all_pipe(d->pipe, i, 1));
	d->pid[0] = fork();
	if (d->pid[0] == -1)
	{
		free(d->pid);
		printf("Error fork()\n");
		free_all_pipe(d->pipe, i, 0);
	}
	else if (d->pid[0] == 0)
		ft_call_process(d);
	waitpid(d->pid[0], NULL, 0);
	free(d->pid);
	free_all_pipe(d->pipe, i, 0);
	return ;
}
