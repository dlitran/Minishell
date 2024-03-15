/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:22:31 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/15 09:10:38 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

static char	*exec_path(t_data *d, char *path)
{
	if (d->cmd->exe && d->cmd->exe[0] == 47 && !access(d->cmd->exe, F_OK))
	{
		path = ft_strdup(d->cmd->exe);
		if (!path)
			return (c_err_msg("error allocating memory for ft_execve\n", 68));
	}
	else
	{
		path = ft_check_path(d->path, d->cmd, d, 0);
		if (!path)
			return (NULL);
	}
	return (path);
}

void	ft_execve(t_data *d, char *path)
{
	pid_t	pid;
	int		status;

	path = exec_path(d, path);
	if (!path)
		return ;
	pid = fork();
	if (pid == -1)
		return (v_err_msg("error fork\n", 69));
	if (pid == 0)
	{
		if (execve(path, d->cmd->arg, d->env) == -1)
			g_error = 63;
		perror("error execve");
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	g_error = status;
	if (status == 256)
		g_error = 1;
	if (status == 512)
		g_error = 2;
	free(path);
}
