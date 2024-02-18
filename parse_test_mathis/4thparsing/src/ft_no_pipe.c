/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:47:33 by dlitran           #+#    #+#             */
/*   Updated: 2024/02/18 16:01:57 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_no_pipe_superior_two(t_data *d)
{
	int	fd2;

	fd2 = open(d->outfile_name, O_WRONLY | O_CREAT | O_APPEND, 0644);//protectar ?
	dup2(fd2, 1);
}

void	ft_no_pipe_superior(t_data *d)
{
	int	fd2;

	fd2 = open(d->outfile_name, O_WRONLY | O_CREAT | O_TRUNC);// protectar ?
	dup2(fd2, 1);
}
/*
void	ft_no_pipe(t_data *d)
{
	int		fd1;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (d->infile > 0)
		{
			fd1 = open(d->cmd->next->exe, O_RDONLY);
			dup2(fd1, 0);
		}
		if (d->outfile == 1)
			ft_no_pipe_superior(d);
		if (d->outfile == 2)
			ft_no_pipe_superior_two(d);
		//execve(ft_check_path(d->path, d->cmd), d->cmd->arg, d->env);
		ft_exec_funcion(d);
	}
	waitpid(pid, NULL, 0);
}*/

void	ft_no_pipe_inferior_two(t_data *d)
{
	int	p[2];
	char	*line;

	pipe(p);
	line = readline("> ");
	while (line && ft_strncmp(line, d->infile_name, ft_strlen(d->cmd->next->exe) + 1))
	{
		write(p[1], line, ft_strlen(line));
		write(p[1], "\n", 1);
		free(line);
		line = readline("> ");
		add_history(line);
	}
	free(line);
	dup2(p[0], 0);
	close(p[0]);
	close(p[1]);
}

void	ft_no_pipe_inferior(t_data *d)
{
	int	fd1;

	fd1 = open(d->infile_name, O_RDONLY);//protectar ?
	dup2(fd1, 0);
}

void	ft_no_pipe(t_data *d)
{
	if (d->infile == 1)
		ft_no_pipe_inferior(d);
	if (d->infile == 2)
		ft_no_pipe_inferior_two(d);
	if (d->outfile == 1)
		ft_no_pipe_superior(d);
	if (d->outfile == 2)
		ft_no_pipe_superior_two(d);
	ft_exec_funcion(d);
}
