/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:54:38 by dlitran           #+#    #+#             */
/*   Updated: 2024/03/13 01:25:40 by mafranco         ###   ########.fr       */
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

void	ft_redirection(t_data *d)
{
	t_cmd	*a;
	int		x;
	int		y;
	int		z;
	int		l;

	x = 0;
	y = 0;
	z = 0;
	l = 0;
	a = d->cmd;
	while (a)
	{
		if (a->inferior - x == 1)
		{
			if (a->infile_name)
				free (a->infile_name);
			a->infile_name = ft_strdup(a->next->exe);
			a = ft_reorganize_cmd(a, a->next);
			x++;
		}
		else if (a->inferior_two - y == 1)
		{
			if (a->infile_name)
				free (a->infile_name);
			a->infile_name = ft_strdup(a->next->exe);
			a = ft_reorganize_cmd(a, a->next);
			y++;
		}
		else if (a->superior - z == 1)
		{
			if (a->outfile_name)
				free (a->outfile_name);
			a->outfile_name = ft_strdup(a->next->exe);
			a = ft_reorganize_cmd(a, a->next);
			z++;
		}
		else if (a->superior_two - l == 1)
		{
			if (a->outfile_name)
				free (a->outfile_name);
			a->outfile_name = ft_strdup(a->next->exe);
			a = ft_reorganize_cmd(a, a->next);
			l++;
		}
		else
		{
			x = 0;
			y = 0;
			z = 0;
			l = 0;
			a = a->next;
		}
	}
	//printf("%s\n", d->infile_name);
	//show_values(d);
	return ;
}
