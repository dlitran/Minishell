/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_with_pipe2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:03:43 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/17 18:11:20 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
/*
void	ft_in_file_1_process(t_data *d, int fd)
{
	char	*file;

	file = d->cmd->infile_name;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_permissions(1, file, 1);
	if (dup2(fd, 0) == -1)
		fd_problem(72, 1);
	if (close (fd) == -1)
		fd_problem(73, 1);
}

void	ft_last_process2(t_data *d, char *file, int fd)
{
	if (d->cmd->superior > 0)
	{
		file = d->cmd->outfile_name;
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			ft_permissions(1, file,  1);
		if (dup2(fd, 1) == -1)
			fd_problem(45, 1);
		if (close(fd) == -1)
			fd_problem(46, 1);
	}
	if (d->cmd->superior_two > 0)
	{
		file = d->cmd->outfile_name;
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			ft_permissions(1, file,  1);
		if (dup2(fd, 1) == -1)
			fd_problem(47, 1);
		if (close(fd) == -1)
			fd_problem(48, 1);
	}
	ft_exec_funcion(d);
}*/
