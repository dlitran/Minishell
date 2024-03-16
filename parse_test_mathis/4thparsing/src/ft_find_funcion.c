/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_funcion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 20:07:26 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/16 19:43:51 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	ft_find_funcion(t_data *d, char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0 && ft_strlen(cmd) == 4)
		return (ft_echo(d));
	if (ft_strncmp(cmd, "cd", 2) == 0 && ft_strlen(cmd) == 2)
		return (ft_cd(d, 0, NULL));
	if (ft_strncmp(cmd, "pwd", 3) == 0 && ft_strlen(cmd) == 3)
		return (ft_pwd(d));
	if (ft_strncmp(cmd, "export", 6) == 0 && ft_strlen(cmd) == 6)
		return (ft_export(d, 1, 0));
	if (ft_strncmp(cmd, "unset", 5) == 0 && ft_strlen(cmd) == 5)
		return (ft_unset(d));
	if (ft_strncmp(cmd, "env", 3) == 0 && ft_strlen(cmd) == 3)
		return (ft_env(d));
	if (ft_strncmp(cmd, "exit", 4) == 0 && ft_strlen(cmd) == 4)
		return (ft_exit(d));
	return (ft_execve(d, NULL));
}

void	ft_exec_funcion(t_data *d)
{
	if (!d->cmd->exe && d->flag_err == 3)
		return ;
	else if (!d->cmd->exe)
	{
		perror("command not found: \n");
		g_error = 39;
		return ;
	}
	ft_find_funcion(d, d->cmd->exe);
	return ;
}
