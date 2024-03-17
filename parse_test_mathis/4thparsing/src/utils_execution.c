/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:54:38 by dlitran           #+#    #+#             */
/*   Updated: 2024/03/17 19:10:25 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int	ft_nb_pipes(t_data *d)
{
	int		nb;
	t_cmd	*a;

	a = d->cmd;
	nb = 0;
	while (a)
	{
		if (a->pipe > 0)
			nb++;
		a = a->next;
	}
	return (nb);
}

t_cmd	*ft_reorganize_cmd(t_cmd *cmd1, t_cmd *cmd2)
{
	char **new_args;
	int	i;
	int	j;
	int	n;

	n = cmd1->nb_arg;
	cmd1->nb_arg = cmd1->nb_arg + cmd2->nb_arg - 1;
	new_args = malloc(sizeof(char *) * (cmd1->nb_arg + 1));
	if (!new_args)
		return (NULL);
	i = 0;
	while (cmd1->arg[i] && i < n)
	{
		new_args[i] = strdup(cmd1->arg[i]);
		if (!new_args[i])
			return (NULL);
		free(cmd1->arg[i]);
		i++;
	}
	free(cmd1->arg);
	cmd1->exe = new_args[0];
	j = 1;
	free(cmd2->arg[0]);
	while (cmd2->arg[j] && i < cmd1->nb_arg)
	{
		new_args[i] = strdup(cmd2->arg[j]);
		if (!new_args[i])
			return (NULL);
		free(cmd2->arg[j]);
		i++;
		j++;
	}
	new_args[i] = NULL;
	cmd1->arg = new_args;
	free(cmd2->arg);
	cmd1->inferior += cmd2->inferior;
	cmd1->inferior_two += cmd2->inferior_two;
	cmd1->superior += cmd2->superior;
	cmd1->superior_two += cmd2->superior_two;
	cmd1->pipe = cmd2->pipe;
	cmd1->next = cmd2->next;
	free(cmd2);
	return (cmd1);
}
/*
void	ft_permissions(int	nb, int close)
{
	g_error = nb;
	ft_putstr_fd(" Permission denied\n", 2);
	if (close == 1)
		exit(g_error);
}*/

int	ft_infile(t_data *d,t_cmd *a, int x)
{
	if (a->infile_name)
		free (a->infile_name);
	a->infile_name = ft_strdup(a->next->exe);
	a->in = open(a->infile_name, O_RDONLY, 0100);
	if (a->in == -1)
	{
		ft_permissions(1, a->infile_name, 0, d->f_err);
		d->f_err = 1;
	}
	a = ft_reorganize_cmd(a, a->next);
	x++;
	return (x);
}

int	ft_infile_two(t_cmd *a, int y)
{
	if (a->infile_name)
		free (a->infile_name);
	a->infile_name = ft_strdup(a->next->exe);
	a = ft_reorganize_cmd(a, a->next);
	y++;
	return (y);
}

int	ft_outfile(t_data *d,t_cmd *a, int z)
{
	if (a->outfile_name)
	{
		close (a->out);
		free (a->outfile_name);
	}
	a->outfile_name = ft_strdup(a->next->exe);
	a->out = open(a->outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (a->out == -1)
	{
		ft_permissions(1, a->outfile_name, 0, d->f_err);
		d->f_err = 1;
	}
	a = ft_reorganize_cmd(a, a->next);
	z++;
	return (z);
}

int	ft_outfile_two(t_data *d, t_cmd *a, int l)
{
	if (a->outfile_name)
	{
		close (a->out);
		free (a->outfile_name);
	}
	a->outfile_name = ft_strdup(a->next->exe);
	a->out = open(a->outfile_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (a->out == -1)
	{
		ft_permissions(1, a->outfile_name, 0, d->f_err);
		d->f_err = 1;
	}
	a = ft_reorganize_cmd(a, a->next);
	l++;
	return (l);
}

int	ft_redirection(t_data *d, int x, int y, int z)
{
	t_cmd	*a;
	int		l;

	l = 0;
	a = d->cmd;
	while (a)
	{
		if (a->inferior - x == 1)
			x = ft_infile(d, a, x);
		else if (a->inferior_two - y == 1)
			y = ft_infile_two(a, y);
		else if (a->superior - z == 1)
			z = ft_outfile(d, a, z);
		else if (a->superior_two - l == 1)
			l = ft_outfile_two(d, a, l);
		else
		{
			x = 0;
			y = 0;
			z = 0;
			l = 0;
			a = a->next;
		}
	}
	return (0);
}
