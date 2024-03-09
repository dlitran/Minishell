/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:22:31 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/09 19:01:56 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

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
	waitpid(pid, &g_error, 0);
	free(path);
}
