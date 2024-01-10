/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_funcion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 20:07:26 by mafranco          #+#    #+#             */
/*   Updated: 2024/01/10 20:59:52 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_find_funcion(t_data *d, int n)
{
	if (ft_strncmp(d->f[n], "echo", 4) == 0 && ft_strlen(d->f[n]) == 4)
		return (ft_echo(d, d->f[n]));
	if (ft_strncmp(d->f[n], "cd", 2) == 0 && ft_strlen(d->f[n]) == 2)
		return (ft_cd(d, d->f[n]));
	if (ft_strncmp(d->f[n], "pwd", 3) == 0 && ft_strlen(d->f[n]) == 3)
		return (ft_pwd(d, d->f[n]));
	if (ft_strncmp(d->f[n], "export", 6) == 0 && ft_strlen(d->f[n]) == 6)
		return (ft_export(d, d->f[n]));
	if (ft_strncmp(d->f[n], "unset", 5) == 0 && ft_strlen(d->f[n]) == 5)
		return (ft_unset(d, d->f[n]));
	if (ft_strncmp(d->f[n], "env", 3) == 0 && ft_strlen(d->f[n]) == 3)
		return (ft_env(d, d->f[n]));
	if (ft_strncmp(d->f[n], "exit", 4) == 0 && ft_strlen(d->f[n]) == 4)
		return (ft_exit(d, d->f[n]));
	if (ft_strncmp(d->f[n], "$", 1) == 0)
		return (ft_dollar_sign(d, d->f[n]));
	return (ft_execve(d, d->f[n]));
}

void	ft_exec_funcion(t_data *d)
{
	if (d->flags.nb_pipe == 0)
		ft_find_funcion(d, 0);
}
