/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:47:33 by dlitran           #+#    #+#             */
/*   Updated: 2024/03/17 19:45:20 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int	ft_no_pipe_superior_two(t_data *d)
{
	if (dup2(d->cmd->out, 1) == -1)
		fd_problem(84, 0, 2, d);
	return (0);
}

int	ft_no_pipe_superior(t_data *d)
{
	if (dup2(d->cmd->out, 1) == -1)
	{
		fd_problem(1, 0, 2, d);
		return (1);
	}
	return (0);
}

void	ft_no_pipe_inferior_two(t_data *d)
{
	int		p[2];
	char	*line;

	pipe(p);
	line = readline("> ");
	while (line
		&& ft_strncmp(line, d->cmd->infile_name, ft_strlen(d->cmd->exe) + 1))
	{
		write(p[1], line, ft_strlen(line));
		write(p[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	if (dup2(p[0], 0) == -1)
		fd_problem(105, 0, 2, d);
	if (close(p[0]) == -1 || close(p[1]) == -1)
		fd_problem(106, 0, 1, d);
}

int	ft_no_pipe_inferior(t_data *d)
{
	if (dup2(d->cmd->in, 0) == -1)
	{
		fd_problem(86, 0, 2, d);
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
