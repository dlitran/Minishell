/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:47:33 by dlitran           #+#    #+#             */
/*   Updated: 2024/03/16 22:10:55 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int	ft_no_pipe_superior_two(t_data *d)
{
	int	fd2;

	fd2 = open(d->cmd->outfile_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd2 == -1)
	{
		fd_problem(1, 0);
		return (1);
	}
	if (dup2(fd2, 1) == -1)
		fd_problem(84, 0);
	return (0);
}

int	ft_no_pipe_superior(t_data *d)
{
	int	fd2;

	fd2 = open(d->cmd->outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd2 == -1)
	{
		fd_problem(1, 0);
		return (1);
	}
	if (dup2(fd2, 1) == -1)
	{
		fd_problem(85, 0);
		return (1);
	}
	return (0);
}

void	ft_no_pipe_inferior_two(t_data *d)
{
	int		p[2];
	char	*line;
	char	*tmp1;

	pipe(p);
	line = readline("> ");
	if (!line)
		return (free_char(NULL, NULL, "error reading line\n", 87));
	tmp1 = ft_strjoin(line, "\n");
	if (!tmp1)
		return (free_char(line, NULL, "error ft_strjoin\n", 88));
	ft_np_inf2_2(d, p, line, tmp1);
}

int	ft_no_pipe_inferior(t_data *d)
{
	int	fd1;

	fd1 = open(d->cmd->infile_name, O_RDONLY);
	if (fd1 == -1)
	{
		fd_problem(1, 0);
		return (1);
	}
	if (dup2(fd1, 0) == -1)
	{
		fd_problem(86, 0);
		return (1);
	}
	return (0);
}

void	ft_no_pipe(t_data *d)
{
	if (d->cmd->inferior > 0)
		if (ft_no_pipe_inferior(d))
			return ;
	if (d->cmd->inferior_two > 0)
		ft_no_pipe_inferior_two(d);
	if (d->cmd->superior > 0)
		if (ft_no_pipe_superior(d))
			return ;
	if (d->cmd->superior_two > 0)
		if (ft_no_pipe_superior_two(d))
			return ;
	ft_exec_funcion(d);
}
