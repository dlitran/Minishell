/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:47:33 by dlitran           #+#    #+#             */
/*   Updated: 2024/03/10 20:11:52 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	ft_no_pipe_superior_two(t_data *d)
{
	int	fd2;

	fd2 = open(d->outfile_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd2 == -1)
	{
		fd_problem(38, 0);
		return (1);
	}
	if (dup2(fd2, 1) == -1)
		fd_problem(84, 0);
	return (0);
}

int	ft_no_pipe_superior(t_data *d)
{
	int	fd2;

	fd2 = open(d->outfile_name, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd2 == -1)
	{
		fd_problem(37, 0);
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
	char	*tmp2;

	pipe(p);
	line = readline("> ");
	if (!line)
		return ;
	tmp1 = ft_strjoin(line, "\n");
	if (!tmp1)
	{
		free(line);
		return ;
	}
	while (line && ft_strncmp(line, d->infile_name,
			ft_strlen(d->cmd->next->exe) + 1))
	{
		write(p[1], line, ft_strlen(line));
		write(p[1], "\n", 1);
		free(line);
		line = readline("> ");
		if (!line)
		{
			free(tmp1);
			return ;
		}
		tmp2 = ft_strjoin(ft_strjoin(tmp1, line), "\n");
		if (!tmp2)
		{
			free(line);
			return ;
		}
		free(tmp1);
		tmp1 = tmp2;
	}
	free(line);
	tmp1 = ft_strjoin(ft_strjoin(d->input, "\n"), tmp2);
	free(tmp2);
	if (!tmp1)
		return ;
	free(d->input);
	d->input = tmp1;
	if (dup2(p[0], 0) == -1)
		return ;
	if (close(p[0]) || close(p[1]))
		return ;
}

int	ft_no_pipe_inferior(t_data *d)
{
	int	fd1;

	fd1 = open(d->infile_name, O_RDONLY);
	if (fd1 == -1)
	{
		fd_problem(36, 0);
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
	if (d->infile == 1)
		if (ft_no_pipe_inferior(d))
			return ;
	if (d->infile == 2)
		ft_no_pipe_inferior_two(d);
	if (d->outfile == 1)
		if (ft_no_pipe_superior(d))
			return ;
	if (d->outfile == 2)
		if (ft_no_pipe_superior_two(d))
			return ;
	ft_exec_funcion(d);
}
