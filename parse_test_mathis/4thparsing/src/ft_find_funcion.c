/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_funcion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 20:07:26 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/08 10:24:35 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_find_funcion(t_data *d, char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0 && ft_strlen(cmd) == 4)
		return (ft_echo(d));
	if (ft_strncmp(cmd, "cd", 2) == 0 && ft_strlen(cmd) == 2)
		return (ft_cd(d));
	if (ft_strncmp(cmd, "pwd", 3) == 0 && ft_strlen(cmd) == 3)
		return (ft_pwd(d));
	if (ft_strncmp(cmd, "export", 6) == 0 && ft_strlen(cmd) == 6)
		return (ft_export(d));
	if (ft_strncmp(cmd, "unset", 5) == 0 && ft_strlen(cmd) == 5)
		return (ft_unset(d));
	if (ft_strncmp(cmd, "env", 3) == 0 && ft_strlen(cmd) == 3)
		return (ft_env(d));
	if (ft_strncmp(cmd, "exit", 4) == 0 && ft_strlen(cmd) == 4)
		return (ft_exit(d));
	if (ft_strncmp(cmd, "$", 1) == 0)
		return (ft_dollar_sign(d));
	return (ft_execve(d));
}

void	ft_exec_funcion(t_data *d)
{
	//char	*buf;

	/*if (d->infile == 2)
	{
		buf = readline()
		while (ft_strncmp(d->cmd->next->exe, buf, ft_strlen(d->cmd->next->exe)))
			ft_find_funcion(d, d->cmd->exe);
	}
	else*/
		ft_find_funcion(d, d->cmd->exe);
	return ;
}
