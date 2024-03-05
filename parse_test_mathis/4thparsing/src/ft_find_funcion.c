/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_funcion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 20:07:26 by mafranco          #+#    #+#             */
/*   Updated: 2024/03/02 21:41:21 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_builtin_redir(t_data *d)
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
}

void	ft_find_funcion(t_data *d, char *cmd)
{
	//ft_builtin_redir(d);
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
		printf("command not found: \n");
		g_error = 39;
		return ;
	}
	ft_find_funcion(d, d->cmd->exe);
	return ;
}
