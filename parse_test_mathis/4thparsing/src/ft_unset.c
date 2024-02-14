/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:09:32 by mafranco          #+#    #+#             */
/*   Updated: 2024/02/14 03:44:14 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	free_env2(char **env, int j)
{
	while (j >= 0)
	{
		free(env[j]);
		j--;
	}
	free(env);
	return (1);
}

int	link_path(t_data *d, char **env)
{
	int		i;
	char	*new;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			new = ft_strdup(env[i]);
			if (!new)
				return (1);
			free(d->path);
			d->path = new;
			return (0);
		}
		i++;
	}
	free(d->path);
	d->path = "";
	return (0);
}

int	unset_env(t_data *d, int j, int len, int k)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * len);
	if (!new)
		return (1);
	while (d->env[i])
	{
		if (i != j)
		{
			new[k] = ft_strdup(d->env[i]);
			if (!new[k])
				return (free_env2(new, k));
			k++;
		}
		i++;
	}
	new[k] = NULL;
	if (link_path(d, new) == 1)
		return (free_env2(new, k));
	free_env2(d->env, i);
	d->env = new;
	return (0);
}

void	ft_unset(t_data *d)
{
	int	j;
	int	i;
	int	len;

	len = 0;
	i = 1;
	while (d->cmd->arg[i])
	{
		j = 0;
		while (d->env[j] && ft_strncmp(d->env[j], d->cmd->arg[i],
				ft_strlen(d->cmd->arg[i])) != 0)
		{
			j++;
		}
		if (d->env[j])
		{
			while (d->env[len])
				len++;
			unset_env(d, j, len, 0);
		}
		i++;
	}
}
