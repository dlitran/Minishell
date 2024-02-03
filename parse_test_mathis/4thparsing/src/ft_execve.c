/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:22:31 by mafranco          #+#    #+#             */
/*   Updated: 2024/01/20 15:36:31 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_execve(t_data *d)
{
	char	*path;
	pid_t	pid;

	path = ft_check_path(d->path, d->cmd);
	if (!path)
		return ;
	pid = fork();
	if (pid == 0)
	{
		execve(path, d->cmd->arg, d->env);
	}
	waitpid(pid, NULL, 0);
	free(path);
}
