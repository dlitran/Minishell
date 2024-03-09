/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_with_pipe2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:03:43 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/05 11:45:07 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_last_process2(t_data *d, char *file, int fd)
{
	if (d->outfile == 1)
	{
		file = d->outfile_name;
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			fd_problem(34, 1);
		dup2(fd, 1);
		close(fd);
	}
	if (d->outfile == 2)
	{
		file = d->outfile_name;
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			fd_problem(35, 1);
		dup2(fd, 1);
		close(fd);
	}
	ft_exec_funcion(d);
}
