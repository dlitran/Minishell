/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:54:38 by dlitran           #+#    #+#             */
/*   Updated: 2024/01/20 13:38:14 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	*free_error_utils(char *slash, char **matrix, int error)
{
	int	i;

	i = 0;
	if (slash)
		free(slash);
	if (matrix)
	{
		while (matrix[i])
			i++;
		i--;
		while (i >= 0)
		{
			free(matrix[i]);
			i--;
		}	
		free(matrix);
	}
	if (error == 1)
		printf("error allocating memory for path\n");
	return (NULL);
}

char	*ft_check_path(char *path, t_cmd *cmd)
{
	char	**matrix;
	int		i;
	char	*slash;
	char	*joined;

	slash = ft_strjoin("/", cmd->exe);
	if (!slash)
		return (free_error_utils(NULL, NULL, 1));
	matrix = ft_split(path, ':');
	if (!matrix)
		return (free_error_utils(slash, NULL, 1));
	i = 0;
	while(matrix[i])
	{
		joined = ft_strjoin(matrix[i], slash);
		if (!joined)
			return (free_error_utils(slash, matrix, 1));
		if (!access(joined, F_OK))
		{
			free_error_utils(slash, matrix, 0);
			return (joined);
		}
		i++;
	}
	//Absolute path of executable
	//Relative path of executable
	free_error_utils(slash, matrix, 0);
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