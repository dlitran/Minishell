/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:54:38 by dlitran           #+#    #+#             */
/*   Updated: 2024/01/19 17:54:38 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*ft_check_path(char *path, t_cmd *cmd)
{
	char	**matrix;
	int		i;
	char	*slash;

	slash = ft_strjoin("/", cmd->exe);
	matrix = ft_split(path, ':'); //protect
	i = 0;
	while(matrix[i])
	{
		if (!access(ft_strjoin(matrix[i], slash), F_OK)) //protect ft_strjoin?
			return (ft_strjoin(matrix[i], slash));
		i++;
	}
	//Absolute path of executable
	//Relative path of executable
	printf("command not found\n");
	return (NULL);
}

int	ft_nb_pipes(t_data *d)
{
	int	nb;
	t_cmd *a;

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

int	ft_infile(t_data *d)
{
	t_cmd *a;

	a = d->cmd;
	while (a)
	{
		if (a->inferior > 0)
			return (1);
		if (a->inferior_two > 0)
			return (2);
		a = a->next;
	}
	return (0);
}

int	ft_outfile(t_data *d)
{
	t_cmd *a;

	a = d->cmd;
	while (a)
	{
		if (a->superior > 0)
			return (1);
		if (a->superior_two > 0)
			return (2);
		a = a->next;
	}
	return (0);
}
